#include <QtWidgets>
#include <QOpenGLWidget>
#include "widget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//	QMainWindow window // already have layout object
	QWidget window;
	//	QDialog window;
	
	Widget *glwindow = new Widget;
//	QOpenGLWidget *glwindow = new QOpenGLWidget();
	QLabel *label = new QLabel(QApplication::translate("windowlayout", "Name:"));
	QLineEdit *lineEdit = new QLineEdit();
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(label);
	layout->addWidget(lineEdit);
	layout->addWidget(glwindow);
	QGroupBox *horizontalGroupBox = new QGroupBox(QDialog::tr("Horizontal layout"));
	horizontalGroupBox->setLayout(layout);
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(horizontalGroupBox);
	
	window.setLayout(mainLayout);
	
	window.setWindowTitle(QApplication::translate("windowlayout", "Window layout"));
	window.show();
	
	return a.exec();
}
