#include <QtWidgets>

/*
 * Layoutにwidgetを追加して、windowにsetLayout
 * 
 * Layoutはwidgetを持てる
 * GroupBoxはLayoutを持てるwidget
 * 
 * MainLayout
 *  |-widget(Label)
 *  |-widget(Button)
 *  |-widget(Others...)
 *  |-widget(GroupBox)
 *              |-widget(Others...)
 *  |-widget(GroupBox)
 *              |-widget(Others...)
 *              |-widget(GroupBox)
 *                          |-widget(Others...)
 * 
 * MainLayout-widgets
 * GroupBox-Layout-widgets
*/

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//	QMainWindow window // already have layout object
	QWidget window; //デフォルトのクラスでウィンドウ生成
	//	QDialog window;
	
	QLabel *label = new QLabel(QApplication::translate("windowlayout", "Name:"));
	QLineEdit *lineEdit = new QLineEdit();
	QHBoxLayout *layout = new QHBoxLayout(); // レイアウトにウィジェットを追加していく
	layout->addWidget(label);
	layout->addWidget(lineEdit);
	QGroupBox *horizontalGroupBox = new QGroupBox(QDialog::tr("Horizontal layout")); // GroupBoxはレイアウトを持つウィジェット→レイアウトを入れ子にできる
	horizontalGroupBox->setLayout(layout);
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(horizontalGroupBox); // GroupBoxはウィジェットなので、レイアウトにそのまま追加できる
	// mainLayout->addWidget();		// 他のオブジェクトも同様に追加可能
			
	window.setLayout(mainLayout); // windowにsetLayout
	
	window.setWindowTitle(QApplication::translate("windowlayout", "Window layout"));
	window.show();
	
	return a.exec();
}
