cmake_minimum_required(VERSION 3.5)

project(Maze VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(view/picturewidget)

set(PROJECT_SOURCES
        main.cc
        view/mainwindow/mainwindow.cc
        view/mainwindow/mainwindow.h
        view/mainwindow/mainwindow.ui

        view/picturewidget/picturewidget.cc
        view/picturewidget/picturewidget.h
        view/picturewidget/mazewidget.cc
        view/picturewidget/mazewidget.h
        view/picturewidget/cavewidget.cc
        view/picturewidget/cavewidget.h
       
        controller/controller.cc
        controller/controller.h

        model/model.h model/model.cc
        model/maze/maze.h model/maze/maze.cc
        model/cave/cave.h model/cave/cave.cc model/maze/maze_gen.cc

        other/maze_matrix.h
        other/maze_matrix.cc

        other/cell.h
        other/mazecell.h
        other/cavecell.h
    
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Maze
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

else()
    if(ANDROID)
        add_library(Maze SHARED
            ${PROJECT_SOURCES}
        )

    else()
        add_executable(Maze
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Maze PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Maze PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Maze)
endif()
