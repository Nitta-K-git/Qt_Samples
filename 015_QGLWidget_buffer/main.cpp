#include "widget.h"

#include <QApplication>

#include <QMenu>
#include <QtWidgets>
#include <QMessageBox>

int main( int argc, char **argv )
{
	QApplication app(argc, argv);
	
	// create widget
	QMainWindow mainWin;
//	MeshViewerWidget w(&mainWin);
//	w.setOptions(opt);
//	mainWin.setCentralWidget(&w);
	
	QGLViewerWidget w(&mainWin);
	mainWin.setCentralWidget(&w);
//	widget.show();
	mainWin.resize(640, 480);
	mainWin.show();
	return app.exec();
}
