# Qt_Samples
Qt basic samples

## ファイル構成

### 001_menu

メニュー作成の最小サンプル

メニューはwindowウィジェットのメソッドして作成。

メニューから呼ばれる関数は任意のクラスのメソッド、今回は同じクラス

### 002_window_in_widget

メニューとボタンウィジェットをwindowクラスで作成。

ボタンがメニューにかぶっているので失敗例

### 003_simple_layout

ウィジェットレイアウト構成の最小サンプル

windowはQWidgetのデフォルトをそのまま使っている

GroupBoxでレイアウトを入れ子にしている(今回はMainLayoutにひとつしか入れてないので、GroupBoxにしなくてもよい)

### 004_glwidget

レイアウトにOpenGL用ウィジェット入れたサンプル

vcglibを使用して物体の描画をしている

### 005_glwidget_min

vcglib無し・描画無しのOpenGL最小構成版

minimumSizeHint,sizeHintが無いとサイズが0になってしまい見えなくなってしまう

### 006_dialog_modal_modeless

メニューをクリックするとモーダルダイアログとモーダレスダイアログを開くだけのサンプル

実際はQDialog継承したクラスで色々ウィジェットを載せておく

### 007_dockWidget

DockWidgetの最小構成サンプル

DockWidgetはdockオブジェクト作って、そこにひとつだけウィジェットをセットする

### 009_widgets_sample

Link:色々なwidgetのサンプル https://doc.qt.io/qt-5/widget-classes.html

groupboxで区切って、mainwindowのcentralに設定

テンプレートとして使う用

### 010_widgets_pushbutton

ボタンの基本的な使い方

### 011_widgets_slider

sliderの基本的な使い方

- sliderが操作されたときに値をシグナルを受け取って表示
- sliderから直接値を取得

### 012_widgets_radiobutton

radiobuttonの基本的な使い方

- QButtonGroupでグループ化して排他Push
- connectでの識別

