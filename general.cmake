# https://stackoverflow.com/questions/22804287/cmake-file-structure-how-to-split-a-cmakelists-txt-into-multiple-files
cmake_minimum_required( VERSION 3.6 )

message("-----load general setting-----")

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>") # 
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/W2>") # warningレベルの変更 3,4だとnoteまで出るのでテンプレート展開で大量にログが出る。https://foonathan.net/blog/2018/10/17/cmake-warnings.html

if(POLICY CMP0074) # https://github.com/PointCloudLibrary/pcl/issues/2425
   cmake_policy(SET CMP0074 NEW)
endif()

# set(Qt5_DIR $ENV{QTDIR})
set(Qt5_DIR C:/Qt2/5.12.3/msvc2017_64)
list(APPEND CMAKE_PREFIX_PATH ${Qt5_DIR})
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Set Automatic MOC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
if(CMAKE_VERSION VERSION_LESS "3.7.0")
   set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(TARGET_LINK_LIBRARIES
   Qt5::Widgets
   Qt5::Core
)

# https://stackoverflow.com/questions/6594796/how-do-i-make-cmake-output-into-a-bin-dir
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

if(NOT CMAKE_DEBUG_POSTFIX)
  set(CMAKE_DEBUG_POSTFIX d)
endif()

