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





