#include "mainwindow.h"

/*
 * QMainWindowでLayout設定する場合はCentralやDockにGroupBox置くのが簡単
*/

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	
	QGroupBox *horizontalGroupBox = new QGroupBox(QDialog::tr("Horizontal layout")); // GroupBoxはレイアウトを持つウィジェット→レイアウトを入れ子にできる
	QVBoxLayout *layout = new QVBoxLayout(); // レイアウトにウィジェットを追加していく
	horizontalGroupBox->setLayout(layout);
	
	QLabel *label = new QLabel(QApplication::translate("windowlayout", "Name:"));
	QLineEdit *lineEdit = new QLineEdit();
	QSlider *slider = new QSlider(Qt::Orientation::Horizontal, this);
	layout->addWidget(label);
	layout->addWidget(lineEdit);
	layout->addWidget(slider);
	
	setCentralWidget(horizontalGroupBox);
	
	setWindowTitle(QApplication::translate("windowlayout", "Window layout"));
}

MainWindow::~MainWindow(){}

