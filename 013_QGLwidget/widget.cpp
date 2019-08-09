#include "widget.h"
#include <gl/GLU.h>

CanvasWidget::CanvasWidget(QWidget *parent, const char *name) : QGLWidget(parent){}

void CanvasWidget::initializeGL(){
	int width = geometry().width();
	int height = geometry().height();
	glViewport(0,0, width, height);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-width *0.5, width*0.5, -height* 0.5, height* 0.5, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);
}
void CanvasWidget::resizeGL( int width, int height ){
	glViewport(0,0,width,height);
}
void CanvasWidget::paintGL(){
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glColor4f(1.0f,0.0f,0.0f,1.0f);
	glBegin(GL_TRIANGLES);
	glVertex3f( -100.0f, 100.0f, 0.0f);
	glVertex3f(-100.0f,-100.0f, 0.0f);
	glVertex3f( 100.0f,-100.0f, 0.0f);
	glEnd();
}
