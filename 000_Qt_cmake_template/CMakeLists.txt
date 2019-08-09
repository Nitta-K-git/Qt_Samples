cmake_minimum_required(VERSION 3.1.0)

project(helloworld CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# set(Qt5_DIR C:/Qt2/5.12.3/msvc2017_64)	# Qtの特定のコンパイラのパスを環境変数に設定するor直接設定
# list(APPEND CMAKE_PREFIX_PATH ${Qt5_DIR})
find_package(Qt5 REQUIRED COMPONENTS Widgets)	# COMPONENTS一覧はlib/cmake以下にあるので参照(e.g. msvc2017_64/lib/cmake)
message(${Qt5_FOUND})
message(${Qt5Widgets_INCLUDE_DIRS})
message(${Qt5Widgets_LIBRARIES})
message(${Qt5Widgets_DEFINITIONS})

add_executable(helloworld
    main.cpp
)

target_link_libraries(helloworld Qt5::Widgets)