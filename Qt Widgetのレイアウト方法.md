# Qt Widgetのレイアウト方法

最小サンプル

```cmake
QT += widgets
SOURCES = main.cpp
```

```cpp
#include <QtWidgets>
int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    QWidget window;
//! [create, lay out widgets and show]
    QLabel *label = new QLabel(QApplication::translate("windowlayout", "Name:"));
    QLineEdit *lineEdit = new QLineEdit();

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addWidget(lineEdit);
    window.setLayout(layout);
//! [create, lay out widgets and show]
    window.setWindowTitle(
        QApplication::translate("windowlayout", "Window layout"));
    window.show();
    return app.exec();
}
```

概要

- Layoutにwidgetを追加して、windowにsetLayout

手順

- QWidget windowでwidnowが生成される
- QHBoxLayoutでlayoutオブジェクト作成
  - layoutに配置したい子Widgetをどんどん追加する
- windowオブジェクトにsetLayoutでレイアウト追加(これは一つしかsetできない。上書きも不可,明示的にdelete必要)
  - layout()メソッドでポインタ取得してポインタを直接deleteする[https://stackoverflow.com/questions/7528680/how-to-delete-an-already-existing-layout-on-a-widget]

# Groupbox

```cmak
QT += widgets
SOURCES = main.cpp
```

```cpp
#include <QtWidgets>

int main(int argc, char *argv[]){
	QApplication a(argc, argv);
	QWidget window;
	//	QDialog window;
	
	QLabel *label = new QLabel(QApplication::translate("windowlayout", "Name:"));
	QLineEdit *lineEdit = new QLineEdit();
	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(label);
	layout->addWidget(lineEdit);
	QGroupBox *horizontalGroupBox = new QGroupBox(QDialog::tr("Horizontal layout"));
	horizontalGroupBox->setLayout(layout);
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(horizontalGroupBox);
	
	window.setLayout(mainLayout);
	
	window.setWindowTitle(QApplication::translate("windowlayout", "Window layout"));
	window.show();
	
	return a.exec();
}
```

概要

- QGroupBoxはlayoutを持ったwidget
  - layoutにwidget入れる
  - QGroupBoxにsetLayout
- 別のlayoutを用意
- QGroupBoxをwidgetとして別のlayoutに入れる
- mainのwindowにsetLayout

# QOpenGLWidgetの追加

```cm
QT += widgets
SOURCES = main.cpp widget.cpp
HEADERS = widget.h
```

widget.h

```cpp
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class Widget : public QOpenGLWidget{
	Q_OBJECT
public:
	Widget(QWidget *parent = nullptr);
	~Widget() override;
	QSize minimumSizeHint() const override; // if not override size property, widget size set (0,0) so invisible
	QSize sizeHint() const override;
protected:
	void initializeGL() override;
	void paintGL() override;
};
#endif // WIDGET_H
```

widget.cpp

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent){}
Widget::~Widget(){}
QSize Widget::minimumSizeHint() const{
	return QSize(50, 50);
}
QSize Widget::sizeHint() const{
	return QSize(400, 400);
}
void Widget::initializeGL(){}
void Widget::paintGL(){}
```

main.cpp

```cpp
#include <QtWidgets>
#include <QOpenGLWidget>
#include "widget.h"

int main(int argc, char *argv[]){
	QApplication a(argc, argv);
	QWidget window;
	//	QDialog window;
	
	Widget *glwindow = new Widget;
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
```

概要

- QOpenGLWidgetを継承して使用する
- sizeHint関連をオーバーライドして1以上の値を返すようにしないと表示されない(そのため、必ず継承したクラスを作る必要がある)
- Widgetのインスタンスを作った後は他のウィジェットと同じ扱い

