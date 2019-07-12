#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
};


#include <QObject>

class ClassA : public QObject{
	Q_OBJECT
public:
	ClassA() { m_value = 0; }
	int value() const { return m_value; }
public slots:
	void setXRotation(int angle);
signals:
	void xRotationChanged(int angle);
private:
	int m_value;
};

class ClassB : public QObject{
	Q_OBJECT
public:
	ClassB() { m_value = 0; }
	int value() const { return m_value; }
public slots:
	void setValue(int value);
signals:
	void valueChanged(int newValue);
private:
	int m_value;
};

#endif // MAINWINDOW_H
