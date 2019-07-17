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
public slots:
	void setSliderValue(int value);
	void getSliderValue();
public:
	QSlider *slider;
	QLabel *label;
	QPushButton *pushButton;
};

#endif // MAINWINDOW_H
