#include "mainwindow.h"
#include <QtWidgets>
#include <QMenu>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	// add menu in MainWindow class
	QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

	// add menu item
	QAction *newAct = new QAction(tr("&New"), this);
	newAct->setShortcuts(QKeySequence::New);
	newAct->setStatusTip(tr("Create a new file"));
	connect(newAct, &QAction::triggered, this, &MainWindow::newFile);
	
	fileMenu->addAction(newAct);
}

MainWindow::~MainWindow()
{
	
}

void MainWindow::newFile(){
	QMessageBox m;
	m.setText("newFile");
	m.exec();
}
