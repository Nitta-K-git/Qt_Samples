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
	
	pushButton = new QPushButton("Push", this);
	layout->addWidget(pushButton);
	
	setCentralWidget(groupBox);
	
	connect(pushButton, &QPushButton::pressed, this, &MainWindow::buttonPushed);
}

MainWindow::~MainWindow(){}

void MainWindow::buttonPushed(){
	QMessageBox msg(this);
	msg.setText("Push!!");
	msg.exec();
}
