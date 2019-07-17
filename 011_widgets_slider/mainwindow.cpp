#include "mainwindow.h"

/*
 * QMainWindowでLayout設定する場合はCentralやDockにGroupBox置くのが簡単
*/

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	QGroupBox *groupBox = new QGroupBox(QDialog::tr("groupBox")); // GroupBoxはレイアウトを持つウィジェット→レイアウトを入れ子にできる
	QHBoxLayout *layout = new QHBoxLayout(); // レイアウトにウィジェットを追加していく
	groupBox->setLayout(layout);
	
	label = new QLabel(QApplication::translate("windowlayout", "Name:"));
	slider = new QSlider(Qt::Orientation::Horizontal, this);
	pushButton = new QPushButton("get slider value", this);
	layout->addWidget(label);
	layout->addWidget(slider);
	layout->addWidget(pushButton);
	
	setCentralWidget(groupBox);
	
	connect(slider, &QSlider::valueChanged, this, &MainWindow::setSliderValue);
	connect(pushButton, &QPushButton::pressed, this, &MainWindow::getSliderValue);
	
	setSliderValue(0);
}

MainWindow::~MainWindow(){}

void MainWindow::setSliderValue(int value){
	QString s("slider value:");
	s += QString::number(value).rightJustified(3,'0'); // フォーマット調整 http://dorafop.my.coocan.jp/Qt/Qt199.html
	label->setText(s);
}
void MainWindow::getSliderValue(){
	int value = slider->value();
	QString s("slider value:");
	s += QString::number(value).rightJustified(3,'0');
	QMessageBox msg(this);
	msg.setText(s);
	msg.exec();
}
