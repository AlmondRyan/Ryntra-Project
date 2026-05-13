cmake_minimum_required(VERSION 3.15)
project(Riko DESCRIPTION "IDE for Ryntra Programming Language")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "D:/Programs/Qt/6.8.0/msvc2022_64/lib/cmake")

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(Riko main.cpp
        Editor/Highlighter/Highlighter.cpp
        Editor/Highlighter/Highlighter.h
        Editor/Highlighter/Color.h
        Editor/Editor/CodeEditor.h
        Editor/Editor/CodeEditor.cpp
        Editor/Editor/LineNumberArea.h
        Resources.qrc
)

target_link_libraries(Riko
        Qt::Core
        Qt::Gui
        Qt::Widgets
)