#include "mainwindow.h"
#include <QtWidgets>
#include <QMenu>
#include <QMessageBox>
#include <QDialog>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent), modelessDlg(nullptr)
{
	// add menu in MainWindow class
	QMenu *dialogMenu = menuBar()->addMenu(tr("&dialog"));

	// add menu item
	QAction *act_modal = new QAction(tr("&modal"), this);
	connect(act_modal, &QAction::triggered, this, &MainWindow::act_modal);

	QAction *act_modeless = new QAction(tr("&modeless"), this);
	connect(act_modeless, &QAction::triggered, this, &MainWindow::act_modeless);
	
	dialogMenu->addAction(act_modal);
	dialogMenu->addAction(act_modeless);
}

MainWindow::~MainWindow(){}

void MainWindow::act_modal(){
	QDialog dlg(this);
	dlg.exec();
}
void MainWindow::act_modeless(){
	if(!modelessDlg){
		modelessDlg = new QDialog(this);
	}
	modelessDlg->show();
	modelessDlg->raise();
	modelessDlg->activateWindow();
}
