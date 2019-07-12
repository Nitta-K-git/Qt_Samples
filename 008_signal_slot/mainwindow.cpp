#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	QMenu *dockMenu = menuBar()->addMenu(tr("Dock"));
	
	QTextEdit *text = new QTextEdit(this);
	setCentralWidget(text);
	
	QDockWidget *dock = new QDockWidget(tr("Customers"), this);
	dock->setFeatures(QDockWidget::DockWidgetMovable); // option デフォルトはすべてenable
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	QListWidget *customerList = new QListWidget(dock); // dockを親に設定
	customerList->addItems(QStringList() << "AAA" << "BBB"); // ListWidgetに適当な文字列追加
	dock->setWidget(customerList); // dockに設定(ウィジェットはひとつだけ設定できる(複数ならgroupBox?))
	addDockWidget(Qt::RightDockWidgetArea, dock); // mainwindowに追加
	dockMenu->addAction(dock->toggleViewAction()); // 表示・非表示をメニューから操作できるアクション
}

MainWindow::~MainWindow(){}

