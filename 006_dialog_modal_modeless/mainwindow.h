#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
	
	void act_modal();
	void act_modeless();
	QDialog *modelessDlg;
};

#endif // MAINWINDOW_H
