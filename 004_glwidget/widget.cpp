#include "widget.h"
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <wrap/qt/device_to_logical.h>
#include <wrap/gl/pick.h>
#include <wrap/qt/gl_label.h>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QtWidgets>

#include <QDebug>

Widget::Widget(QWidget *parent)
	: QOpenGLWidget(parent), 
	  xRot(0),
	  yRot(0),
	  zRot(0),
	  camera_dist(-15)
{
//	vcg::tri::Octahedron(mesh);
	vcg::tri::Dodecahedron(mesh);
	
	vcg::tri::UpdateNormal<CMeshO>::PerFace(mesh);
	attrVertex = vcg::tri::Allocator<CMeshO>::GetPerMeshAttribute<QVector<QVector3D>>(mesh,"vertex");
	attrVertexNormal = vcg::tri::Allocator<CMeshO>::GetPerMeshAttribute<QVector<QVector3D>>(mesh,"normal");
	
	// init attrVertex and vertex index array
	vertices = &attrVertex();
	normals = &attrVertexNormal();
	CMeshO::FaceIterator fi;
	for(fi=mesh.face.begin(); fi!=mesh.face.end(); ++fi){
		CMeshO::FacePointer pf = &*fi;
		for(int k=0; k<pf->VN(); ++k){
			CVertexO *pv = pf->cV(k);
			QVector3D p(pv->P()[0], pv->P()[1], pv->P()[2]);
			vertices->push_back(p);
			// init color
			colors.push_back(QVector3D(1,0,0));
			// init attrVertexNormal
			QVector3D n(fi->N()[0], fi->N()[1], fi->N()[2]); // use face normal
			normals->push_back(n);
		}
	}
}
Widget::~Widget(){
}

QSize Widget::minimumSizeHint() const{
	return QSize(50, 50);
}

QSize Widget::sizeHint() const{
	return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360 * 16)
		angle -= 360 * 16;
}

void Widget::setXRotation(int angle){
	qNormalizeAngle(angle);
	if (angle != xRot) {
		xRot = angle;
		emit xRotationChanged(angle);
		update();
	}
}

void Widget::setYRotation(int angle){
	qNormalizeAngle(angle);
	if (angle != yRot) {
		yRot = angle;
		emit yRotationChanged(angle);
		update();
	}
}

void Widget::setZRotation(int angle){
	qNormalizeAngle(angle);
	if (angle != zRot) {
		zRot = angle;
		emit zRotationChanged(angle);
		update();
	}
}

void Widget::initializeGL(){
	program = new QOpenGLShaderProgram;
	program->addShaderFromSourceCode(
				QOpenGLShader::Vertex, 
				"attribute vec4 vertex;\n"
				"attribute vec3 normal;\n"
				"attribute vec3 color;\n"
				"varying vec3 vert;\n" // pass to fragment
				"varying vec3 vertNormal;\n"
				"varying vec3 vertColor;\n"
				"uniform mat4 projMat;\n"
				"uniform mat4 moveMat;\n"
				"uniform mat3 normalMatrix;\n" // world matrix normal
				"void main(void)\n"
				"{\n"
				"   vert = vertex.xyz;\n"
				"   vertNormal = normalMatrix * normal;\n"
				"   vertColor = color.rgb;\n"
				"   gl_Position = projMat * moveMat * vertex;\n"
				"   gl_PointSize = 300.0 / gl_Position.w;\n"
				"}"
				);
	program->addShaderFromSourceCode(
				QOpenGLShader::Fragment, 
				"varying highp vec3 vert;\n"
				"varying highp vec3 vertNormal;\n"
				"varying highp vec3 vertColor;\n"
				"uniform highp vec3 lightPos;\n"
				"void main(void)\n"
				"{\n"
//				"   gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);\n"
				"   highp vec3 L = normalize(lightPos - vert);\n"
				"   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
//				"   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
				"   highp vec3 color = vertColor;\n"
				"   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
				"   gl_FragColor = vec4(col, 1.0);\n"
				"}"
				);
	program->bindAttributeLocation("vertex", vertexLoc);
	program->bindAttributeLocation("normal", normalLoc);
	program->bindAttributeLocation("color", colorLoc);
	
	program->link();
	program->bind();
	
	projMatLocation = program->uniformLocation("projMat");
	moveMatLocation = program->uniformLocation("moveMat");
	lightPosLocation = program->uniformLocation("lightPos");
	normalMatrixLocation = program->uniformLocation("normalMatrix");
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	world.setToIdentity();
	proj.setToIdentity();
	camera.setToIdentity();
}
void Widget::paintGL(){
	QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
	
	f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	f->glEnable(GL_DEPTH_TEST);
	f->glEnable(GL_CULL_FACE);
//	f->glEnable(GL_VERTEX_PROGRAM_POINT_SIZE); // gl_PointSize in vertex shader
//	f->glEnable(GL_POINT_SPRITE);	// enable gl_PointCoord in fragment shader -> can not use current gl version

	world.setToIdentity();
	world.rotate(180.0f - (xRot / 16.0f), 1, 0, 0);
	world.rotate(yRot / 16.0f, 0, 1, 0);
	world.rotate(zRot / 16.0f, 0, 0, 1);
	
	camera.setToIdentity();
	camera.translate(0,0,camera_dist);
	
	program->bind();
	
	program->setUniformValue(lightPosLocation, QVector3D(70, 70, 70));
	program->enableAttributeArray(normalMatrixLocation);
	program->setUniformValue(normalMatrixLocation, world.normalMatrix());
	program->enableAttributeArray(vertexLoc);
	program->setAttributeArray(vertexLoc, vertices->constData());
	program->enableAttributeArray(normalLoc);
	program->setAttributeArray(normalLoc, normals->constData());
	program->enableAttributeArray(colorLoc);
	program->setAttributeArray(colorLoc, colors.constData());
	program->setUniformValue(projMatLocation, proj);
	program->setUniformValue(moveMatLocation, camera*world);
	
	f->glDrawArrays(GL_TRIANGLES, 0, vertices->size());
}
void Widget::resizeGL(int w, int h){
	proj.setToIdentity();
	proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void Widget::mousePressEvent(QMouseEvent *event){
	lastPos = event->pos();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - lastPos.x();
	int dy = event->y() - lastPos.y();
	
	if (event->buttons() & Qt::LeftButton) {
		setXRotation(xRot - 8 * dy);
		setYRotation(yRot - 8 * dx);
	} else if (event->buttons() & Qt::RightButton) {
		setXRotation(xRot - 8 * dy);
		setZRotation(zRot - 8 * dx);
	}
	lastPos = event->pos();
}

void Widget::mouseReleaseEvent(QMouseEvent *event){
	(void)event;
}

void Widget::wheelEvent(QWheelEvent *event){
	int degrees = event->angleDelta().y() / 8;
	camera_dist += degrees/10;
	if(camera_dist>=0){camera_dist=0;}
//	qDebug() << camera_dist;
	update();
}

