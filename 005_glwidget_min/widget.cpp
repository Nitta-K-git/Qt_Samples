#include "widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent){}
Widget::~Widget(){}

QSize Widget::minimumSizeHint() const{
	return QSize(50, 50);
}

QSize Widget::sizeHint() const{
	return QSize(400, 400);
}
void Widget::initializeGL(){}
void Widget::paintGL(){}

