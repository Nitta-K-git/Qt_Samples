cmake_minimum_required( VERSION 3.6 )

# Create Project
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME) # https://stackoverflow.com/questions/12344368/automatically-use-the-directory-as-the-project-name-in-cmake
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} CXX)
message(${ProjectId})

# include(../general.cmake) # https://stackoverflow.com/questions/22804287/cmake-file-structure-how-to-split-a-cmakelists-txt-into-multiple-files

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

set(SOURCE_FILES
   main.cpp
   mainwindow.cpp
   mainwindow.h
)

# QGLWidget Setting
# find_package(Qt5 COMPONENTS OpenGL REQUIRED)
# find_package(OpenGL)
# set(TARGET_LINK_LIBRARIES
# ${TARGET_LINK_LIBRARIES}
# Qt5::OpenGL
# ${OPENGL_LIBRARIES}
# )

# Add Executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}) # https://stackoverflow.com/questions/28893450/how-to-get-debug-postfix-in-executable-name/29023980

target_link_libraries(${PROJECT_NAME} ${TARGET_LINK_LIBRARIES})
