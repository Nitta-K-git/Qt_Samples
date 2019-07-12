# 出力ファイルをoutフォルダに設定(これは任意)
DESTDIR = $$clean_path($$_PRO_FILE_PWD_/../out)

win32{win32-msvc{QMAKE_CXXFLAGS += /utf-8}} # visual studioはUTF-8用の指定が必要
