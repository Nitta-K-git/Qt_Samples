#ifndef WIDGET_H
#define WIDGET_H

#include <QGLWidget>
#include <QVector3D>
#include <QMatrix4x4>
#include <string>
#include <vector>
#include <map>

class QGLViewerWidget : public QGLWidget{
	Q_OBJECT
public:
	typedef QGLWidget Super;
	// Default constructor.
	explicit QGLViewerWidget( QWidget* _parent=0 );
	QGLViewerWidget( QGLFormat& _fmt, QWidget* _parent=0 );
	virtual ~QGLViewerWidget();
private:
	void init(void);
	
public:
	/* Sets the center and size of the whole scene. 
	 The _center is used as fixpoint for rotations and for adjusting
	 the camera/viewer (see view_all()). */
	void set_scene_pos( const QVector3D& _center, float _radius );  
	
	/* view the whole scene: the eye point is moved far enough from the
	 center so that the whole scene is visible. */
	void view_all();
	
	float radius() const { return radius_; }
	const QVector3D& center() const { return center_; }
	
	const GLfloat* modelview_matrix() const  { return modelview_matrix_;  }
	const GLfloat* projection_matrix() const { return projection_matrix_; }
	
	float fovy() const { return 45.0f; }
protected:
	// draw the scene: will be called by the painGL() method.
	virtual void draw_scene(const std::string& _draw_mode);
	
	void setDefaultMaterial(void);
	void setDefaultLight(void);
	
private: // inherited
	// initialize OpenGL states (triggered by Qt)
	void initializeGL();
	// draw the scene (triggered by Qt)
	void paintGL();
	// handle resize events (triggered by Qt)
	void resizeGL( int w, int h );
protected:
	// Qt mouse events
	virtual void mousePressEvent( QMouseEvent* );
	virtual void mouseReleaseEvent( QMouseEvent* );
	virtual void mouseMoveEvent( QMouseEvent* );
	virtual void wheelEvent( QWheelEvent* );
	virtual void keyPressEvent( QKeyEvent* );
	
private:
	// updates projection matrix
	void update_projection_matrix();
	// translate the scene and update modelview matrix
	void translate(const QVector3D& _trans);
	// rotate the scene (around its center) and update modelview matrix
	void rotate(const QVector3D& _axis, float _angle);
	
	QVector3D  center_;
	float radius_;
	
	GLfloat projection_matrix_[16],	modelview_matrix_[16];
	
	// virtual trackball: map 2D screen point to unit sphere
	bool map_to_sphere(const QPoint& _point, QVector3D& _result);
	
	QPoint           last_point_2D_;
	QVector3D  last_point_3D_;
	bool             last_point_ok_;
};


#endif // WIDGET_H
