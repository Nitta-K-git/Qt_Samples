#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class Widget : public QOpenGLWidget{
	Q_OBJECT
public:
	Widget(QWidget *parent = nullptr);
	~Widget() override;
	
	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;
	
protected:
	void initializeGL() override;
	void paintGL() override;
//	void resizeGL(int width, int height) override;
//	QOpenGLShaderProgram *program;
};

#endif // WIDGET_H
