#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>

#include <QMatrix4x4>
#include <QVector>
#include <QVector3D>

#include <common/ml_mesh_type.h>
#include <vcg/complex/algorithms/create/platonic.h>
#include <vcg/complex/complex.h>

#include <QMenu>
#include <QMainWindow>

#include <QtDebug>

class Widget : public QOpenGLWidget
{
	Q_OBJECT
public:
	Widget(QWidget *parent = 0);
	~Widget();
	
public slots:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;
	
signals:
	void xRotationChanged(int angle);
	void yRotationChanged(int angle);
	void zRotationChanged(int angle);
	
protected:
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int width, int height) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void wheelEvent(QWheelEvent *event) override;
private:
	int xRot;
	int yRot;
	int zRot;
	float camera_dist;
	QPoint lastPos;
	
	enum{
		vertexLoc = 0,
		normalLoc = 1,
		colorLoc = 2, 
	};
	QOpenGLShaderProgram *program;
	QMatrix4x4 proj;
	QMatrix4x4 camera;
	QMatrix4x4 world;
	QVector<QVector3D> *vertices;
	QVector<QVector3D> *normals;
	QVector<QVector3D> colors;
	
	int projMatLocation;
	int moveMatLocation;
	int normalMatrixLocation;
	int lightPosLocation;
	
	CMeshO mesh;
	CMeshO::PerMeshAttributeHandle<QVector<QVector3D>> attrVertex;
	CMeshO::PerMeshAttributeHandle<QVector<QVector3D>> attrVertexNormal;
};

#endif // WIDGET_H
