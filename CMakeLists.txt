cmake_minimum_required(VERSION 3.16)

project(cppWeChat_Client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        MainWidget.cpp
        MainWidget.h
        MainWidget.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(cppWeChat_Client
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resource.qrc
        data.h
        WindowMid/SessionFriendArea.h
        WindowRight/MessageEditArea.h WindowRight/MessageShowArea.h
        Dialog/FriendInfoArea.h Dialog/SessionTailMoreArea.h Dialog/UserInfoArea.h
        Dialog/FriendInfoArea.cpp Dialog/SessionTailMoreArea.cpp Dialog/UserInfoArea.cpp
        WindowMid/SessionFriendArea.cpp
        WindowRight/MessageEditArea.cpp WindowRight/MessageShowArea.cpp
        WindowMid/SessionFriendItem.h WindowMid/SessionFriendItem.cpp
        WindowMid/SessionItem.h WindowMid/SessionItem.cpp
        WindowMid/FriendItem.h WindowMid/FriendItem.cpp
        WindowMid/FriendApplyItem.h WindowMid/FriendApplyItem.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET cppWeChat_Client APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(cppWeChat_Client SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(cppWeChat_Client
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(cppWeChat_Client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.cppWeChat_Client)
endif()
set_target_properties(cppWeChat_Client PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS cppWeChat_Client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(cppWeChat_Client)
endif()
