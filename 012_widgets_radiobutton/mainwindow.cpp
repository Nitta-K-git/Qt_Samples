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
	
	label = new QLabel("Push ID:  ", this);
	layout->addWidget(label);
	
	QButtonGroup *buttonGroup = new QButtonGroup(this);
	
	QRadioButton *radioButton1 = new QRadioButton("radio1", this);
	QRadioButton *radioButton2 = new QRadioButton("radio2", this);
	QRadioButton *radioButton3 = new QRadioButton("radio3", this);
	buttonGroup->addButton(radioButton1, 1);
	buttonGroup->addButton(radioButton2, 2);
	buttonGroup->addButton(radioButton3, 3);

	QButtonGroup *buttonGroup2 = new QButtonGroup(this);
	QRadioButton *radioButton4 = new QRadioButton("radio4", this);
	QRadioButton *radioButton5 = new QRadioButton("radio5", this);
	buttonGroup2->addButton(radioButton4, 4);
	buttonGroup2->addButton(radioButton5, 5);
	
	layout->addWidget(radioButton1);
	layout->addWidget(radioButton2);
	layout->addWidget(radioButton3);
	layout->addWidget(radioButton4);
	layout->addWidget(radioButton5);
	
	setCentralWidget(groupBox);
	
	// 初期値設定
	radioButton1->setChecked(true);
	radioButton2->setChecked(true); // 1,2は同じグループなので、2をcheckすると自動的に1は解除される
	radioButton4->setChecked(true);
	
	connect(buttonGroup, qOverload<int>(&QButtonGroup::buttonPressed), this, &MainWindow::buttonPressed); // ラジオボタンのイベントはButtonGroupで受け取ると楽
		// buttonPressed はQAbstractButton *とintの2種類あるので、明示的に指定する
		// https://qiita.com/argama147/items/30da69e4c1088917d522
}

MainWindow::~MainWindow(){}

void MainWindow::buttonPressed(int id){
	label->setText(QString("Push ID:")+QString::number(id).rightJustified(2,' '));
	// ここでmessageBoxを使って表示するとラジオボタンの状態が変わらない(イベントが途中で遮られるっぽい？)
}
