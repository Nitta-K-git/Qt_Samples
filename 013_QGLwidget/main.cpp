#include "widget.h"

#include <QApplication>

#include <QMenu>
#include <QtWidgets>
#include <QMessageBox>

int main( int argc, char **argv )
{
	QApplication app(argc, argv);
	CanvasWidget widget;
	widget.setGeometry( 100, 100, 200, 300 );
	widget.show();
	return app.exec();
}
