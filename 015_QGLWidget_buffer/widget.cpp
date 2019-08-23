//#ifdef _MSC_VER
//#  pragma warning(disable: 4267 4311 4305)
//#endif

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <QApplication>
#include <QCursor>
#include <QDateTime>
#include <QImage>
#include <QMenu>
#include <QMouseEvent>
// --------------------
//#include <OpenMesh/Tools/Utils/Timer.hh>
#include "widget.h"

#if !defined(M_PI)
#define M_PI 3.1415926535897932
#endif

#include <gl/GL.h>
#include <gl/GLU.h>

const double TRACKBALL_RADIUS = 0.6;

using namespace Qt;
//using namespace OpenMesh;

QGLViewerWidget::QGLViewerWidget(QWidget *_parent)
	: QGLWidget(_parent) {
	init();
}

QGLViewerWidget::
QGLViewerWidget(QGLFormat &_fmt, QWidget *_parent)
	: QGLWidget(_fmt, _parent) {
	init();
}

void QGLViewerWidget::init(void) {
	// qt stuff
	setAttribute(Qt::WA_NoSystemBackground, true);
	setFocusPolicy(Qt::StrongFocus);
	setAcceptDrops(true);
	setCursor(Qt::PointingHandCursor);
}

QGLViewerWidget::~QGLViewerWidget() {}

void QGLViewerWidget::setDefaultMaterial(void) {
	GLfloat mat_a[] = {0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat mat_d[] = {0.7f, 0.7f, 0.5f, 1.0f};
	GLfloat mat_s[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat shine[] = {120.0f};
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_a);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_d);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_s);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}

void QGLViewerWidget::setDefaultLight(void) {
	GLfloat pos1[] = {0.1f, 0.1f, -0.02f, 0.0f};
	GLfloat pos2[] = {-0.1f, 0.1f, -0.02f, 0.0f};
	GLfloat pos3[] = {0.0f, 0.0f, 0.1f, 0.0f};
	GLfloat col1[] = {0.7f, 0.7f, 0.8f, 1.0f};
	GLfloat col2[] = {0.8f, 0.7f, 0.7f, 1.0f};
	GLfloat col3[] = {1.0f, 1.0f, 1.0f, 1.0f};
	
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, pos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, col1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, col1);
	
	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, pos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, col2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, col2);
	
	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_POSITION, pos3);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, col3);
	glLightfv(GL_LIGHT2, GL_SPECULAR, col3);
}

void QGLViewerWidget::initializeGL() {
	// OpenGL state
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glDisable(GL_DITHER);
	glEnable(GL_DEPTH_TEST);
	
	// Material
	setDefaultMaterial();
	
	// Lighting
	glLoadIdentity();
	setDefaultLight();
	
	// Fog
	GLfloat fogColor[4] = {0.3f, 0.3f, 0.4f, 1.0f};
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.35f);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, 5.0f);
	glFogf(GL_FOG_END, 25.0f);
	
	// scene pos and size
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix_);
	set_scene_pos(QVector3D(0.0, 0.0, 0.0), 1.0);
}

void QGLViewerWidget::resizeGL(int _w, int _h) {
	update_projection_matrix();
	glViewport(0, 0, _w, _h);
	updateGL();
}

void QGLViewerWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(projection_matrix_);
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(modelview_matrix_);
	
	draw_scene("Wireframe");
}

void glutWireTeapot(double r){
	glColor3f(1,0,0);
	glBegin(GL_TRIANGLES);
//	glBegin(GL_LINE_STRIP);
	glVertex3f(-5,-5,0);
	glVertex3f(-5,5,0);
	glVertex3f(0,5,0);

	glVertex3f(-15,-5,-5);
	glVertex3f(-5,5,-5);
	glVertex3f(0,5,-5);
	glVertex3f(5,-5,5);
	glVertex3f(-5,5,5);
	glVertex3f(0,5,5);
	glEnd();
}
void glutSolidTeapot(double r){
	glutWireTeapot(r);
}
void QGLViewerWidget::draw_scene(const std::string &_draw_mode) {
	if(_draw_mode == "Wireframe") {
		glDisable(GL_LIGHTING);
		 glutWireTeapot(0.5);
	}
	else if(_draw_mode == "Solid Flat") {
		glEnable(GL_LIGHTING);
		glShadeModel(GL_FLAT);
		glutSolidTeapot(0.5);
	}
	else if(_draw_mode == "Solid Smooth") {
		glEnable(GL_LIGHTING);
		glShadeModel(GL_SMOOTH);
		glutSolidTeapot(0.5);
	}else{
		glDisable(GL_LIGHTING);
		glutWireTeapot(0.5);
	}
}

void QGLViewerWidget::mousePressEvent(QMouseEvent *_event) {
	// popup menu
	if(_event->button() == Qt::RightButton && _event->buttons() == Qt::RightButton) {
	}else{
		last_point_ok_ = map_to_sphere(last_point_2D_ = _event->pos(), last_point_3D_);
	}
}

void QGLViewerWidget::mouseMoveEvent(QMouseEvent *_event) {
	QPoint newPoint2D = _event->pos();
	
	// Left button: rotate around center_
	// Middle button: translate object
	// Left & middle button: zoom in/out
	
	QVector3D newPoint3D;
	bool newPoint_hitSphere = map_to_sphere(newPoint2D, newPoint3D);
	
	float dx = newPoint2D.x() - last_point_2D_.x();
	float dy = newPoint2D.y() - last_point_2D_.y();
	
	float w = width();
	float h = height();
	
	// enable GL context
	makeCurrent();
	
	// move in z direction
	if((_event->buttons() == (LeftButton + MidButton)) || (_event->buttons() == LeftButton && _event->modifiers() == ControlModifier)) {
		float value_y = radius_ * dy * 3.0 / h;
		translate(QVector3D(0.0, 0.0, value_y));
	}
	// move in x,y direction
	else if((_event->buttons() == MidButton) || (_event->buttons() == LeftButton && _event->modifiers() == AltModifier)) {
		float z = -(modelview_matrix_[2] * center_[0] +
				  modelview_matrix_[6] * center_[1] +
				  modelview_matrix_[10] * center_[2] +
				  modelview_matrix_[14]) /
				(modelview_matrix_[3] * center_[0] +
				modelview_matrix_[7] * center_[1] +
				modelview_matrix_[11] * center_[2] +
				modelview_matrix_[15]);
		
		float aspect = w / h;
		float near_plane = 0.01 * radius_;
		float top = tan(fovy() / 2.0f * M_PI / 180.0f) * near_plane; // fovyの2等分角のラジアンのtan * 隣接辺 = near_plane上での対角辺の長さ
		float right = aspect * top; // near_plane上の横幅/2の長さ
		
		translate(QVector3D(2.0 * dx / w * right / near_plane * z,
						-2.0 * dy / h * top / near_plane * z,
						0.0f));
	}
	// rotate
	else if(_event->buttons() == LeftButton) {
		if(last_point_ok_) {
			if((newPoint_hitSphere = map_to_sphere(newPoint2D, newPoint3D))) {
				QVector3D axis = QVector3D::crossProduct(last_point_3D_, newPoint3D);
				if(axis.lengthSquared() < 1e-7) {
					axis = QVector3D(1, 0, 0);
				} else {
					axis.normalize();
				}
				// find the amount of rotation
				QVector3D d = last_point_3D_ - newPoint3D;
				float t = 0.5 * d.length() / TRACKBALL_RADIUS;
				if(t < -1.0)
					t = -1.0;
				else if(t > 1.0)
					t = 1.0;
				float phi = 2.0 * asin(t);
				float angle = phi * 180.0 / M_PI;
				rotate(axis, angle);
			}
		}
	}
	
	// remember this point
	last_point_2D_ = newPoint2D;
	last_point_3D_ = newPoint3D;
	last_point_ok_ = newPoint_hitSphere;
	
	// trigger redraw
	updateGL();
}

void QGLViewerWidget::mouseReleaseEvent(QMouseEvent * /* _event */) {
	last_point_ok_ = false;
}

void QGLViewerWidget::wheelEvent(QWheelEvent *_event) {
	// Use the mouse wheel to zoom in/out
	float d = -(float)_event->delta() / 120.0 * 0.2 * radius_;
	translate(QVector3D(0.0, 0.0, d));
	updateGL();
	_event->accept();
}

void QGLViewerWidget::translate(const QVector3D &_trans) {
	// Translate the object by _trans
	// Update modelview_matrix_
	makeCurrent();
	glLoadIdentity();
	glTranslatef(_trans[0], _trans[1], _trans[2]);
	glMultMatrixf(modelview_matrix_);
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix_);
}

void QGLViewerWidget::rotate(const QVector3D &_axis, float _angle) {
	// Rotate around center center_, axis _axis, by angle _angle
	// Update modelview_matrix_
	
	QVector3D t(modelview_matrix_[0] * center_[0] +
			modelview_matrix_[4] * center_[1] +
			modelview_matrix_[8] * center_[2] +
			modelview_matrix_[12],
			modelview_matrix_[1] * center_[0] +
			modelview_matrix_[5] * center_[1] +
			modelview_matrix_[9] * center_[2] +
			modelview_matrix_[13],
			modelview_matrix_[2] * center_[0] +
			modelview_matrix_[6] * center_[1] +
			modelview_matrix_[10] * center_[2] +
			modelview_matrix_[14]);
	
	makeCurrent();
	glLoadIdentity();
	glTranslatef(t[0], t[1], t[2]);
	glRotatef(_angle, _axis[0], _axis[1], _axis[2]);
	glTranslatef(-t[0], -t[1], -t[2]);
	glMultMatrixf(modelview_matrix_);
	glGetFloatv(GL_MODELVIEW_MATRIX, modelview_matrix_);
}

bool QGLViewerWidget::map_to_sphere(const QPoint &_v2D, QVector3D &_v3D) {
	// This is actually doing the Sphere/Hyperbolic sheet hybrid thing,
	// based on Ken Shoemake's ArcBall in Graphics Gems IV, 1993.
	double x = (2.0 * _v2D.x() - width()) / width();
	double y = -(2.0 * _v2D.y() - height()) / height();
	double xval = x;
	double yval = y;
	double x2y2 = xval * xval + yval * yval;
	
	const double rsqr = TRACKBALL_RADIUS * TRACKBALL_RADIUS;
	_v3D[0] = xval;
	_v3D[1] = yval;
	if(x2y2 < 0.5 * rsqr) {
		_v3D[2] = sqrt(rsqr - x2y2);
	} else {
		_v3D[2] = 0.5 * rsqr / sqrt(x2y2);
	}
	return true;
}

void QGLViewerWidget::update_projection_matrix() {
	makeCurrent();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	const double fovY = 45.0;
	const double aspect = static_cast<double>(width()) / static_cast<double>(height());
	const double zNear = 0.01 * radius_;
	const double zFar = 100.0 * radius_;
	
	//  Replacement for: gluPerspective(45.0, (GLfloat) width() / (GLfloat) height(), 0.01*radius_, 100.0*radius_);
	const double pi = 3.1415926535897932384626433832795;
	const double fH = tan(fovY / 360 * pi) * zNear;
	const double fW = fH * aspect;
	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
	
	glGetFloatv(GL_PROJECTION_MATRIX, projection_matrix_);
	glMatrixMode(GL_MODELVIEW);
}

void QGLViewerWidget::view_all() {
	translate(QVector3D(-(modelview_matrix_[0] * center_[0] +
			  modelview_matrix_[4] * center_[1] +
			modelview_matrix_[8] * center_[2] +
			modelview_matrix_[12]),
			-(modelview_matrix_[1] * center_[0] +
			modelview_matrix_[5] * center_[1] +
			modelview_matrix_[9] * center_[2] +
			modelview_matrix_[13]),
			-(modelview_matrix_[2] * center_[0] +
			modelview_matrix_[6] * center_[1] +
			modelview_matrix_[10] * center_[2] +
			modelview_matrix_[14] +
			3.0f * radius_)));
}

void QGLViewerWidget::set_scene_pos(const QVector3D &_cog, float _radius) {
	center_ = _cog;
	radius_ = _radius;
	glFogf(GL_FOG_START, 1.5f * _radius);
	glFogf(GL_FOG_END, 3.0f * _radius);
	
	update_projection_matrix();
	view_all();
}

void QGLViewerWidget::keyPressEvent( QKeyEvent* _event){
	switch( _event->key() ){
	case Key_H:
//		std::cout << ;
		break;
	case Key_P:
		break;
	}
	_event->ignore();
}
void QGLViewerWidget::setup_buffer_object(){
	GLfloat vertices[] = {
		-0.7f, -0.7f, 0.0f,
		0.7f,-0.7f, 0.0f,
		0.7f, 0.7f, 0.0f,
		-0.7f,0.7f, 0.0f
	};
	
	GLfloat colors[] = {
		1.0f, 1.0f, 0.0f, 1.0f,
		0.5f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f
	};
	
	int indices[] = {0, 1, 2, 0, 3, 2};
	
//	glGenVertexArrays(1, &vao);
//	glGenBuffers(1, &vertex_vbo);
//	glGenBuffers(1, &color_vbo);
//	glGenBuffers(1, &ebo);
	
//	glBindVertexArray(vao);
	
//	// Position attribute
//	glBindBuffer(GL_ARRAY_BUFFER, vertex_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	
//	// Color attribute
//	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	
//	// Element Array Buffer
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
}
