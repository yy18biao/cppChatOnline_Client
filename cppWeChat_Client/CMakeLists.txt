cmake_minimum_required(VERSION 3.16)
project(cppWeChat_Client LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    MainWidget.ui
    MainWidget.h
    MainWidget.cpp
    MessageEditArea.cpp
    MessageEditArea.h
    MessageShowArea.cpp
    MessageShowArea.h
    SessionFriendArea.cpp
    SessionFriendArea.h
    UserInfoArea.cpp
    UserInfoArea.h
    FriendInfoArea.cpp
    FriendInfoArea.h
    resource.qrc
)

qt6_add_resources(MY_RESOURCES_RCC resource.qrc)

qt_add_executable(cppWeChat_Client ${PROJECT_SOURCES} ${MY_RESOURCES_RCC})

set_target_properties(cppWeChat_Client
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(cppWeChat_Client
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
