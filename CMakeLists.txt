cmake_minimum_required(VERSION 3.21.1)
project(UndertaleSaveEditor VERSION 2.1.0.0 LANGUAGES CXX)

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)

if(!supported)
    message(FATAL_ERROR "Interprocedural Optimization is not supported: ${error}")
endif()

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Network Widgets)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    enable_language("RC")
    set(WIN32_ICON ${CMAKE_CURRENT_SOURCE_DIR}/icon.rc)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "fi.cofeiini.${PROJECT_NAME}")
    set(MACOSX_BUNDLE_ICON_FILE icon.icns)
    set(MACOSX_ICON "${CMAKE_CURRENT_SOURCE_DIR}/images/icon.icns")
    set_source_files_properties(${MACOSX_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
    src/core/dialogs.cpp
    src/core/dialogs.h
    src/core/initools.cpp
    src/core/initools.h
    src/core/mainwindow.cpp
    src/core/mainwindow.h
    src/core/pages.cpp
    src/core/pages.h
    src/core/tools.cpp
    src/core/tools.h
    src/filedownloader.h
    src/helpers.h
    src/main.cpp
    resources.qrc
    ${MACOSX_ICON}
    ${WIN32_ICON}
)

target_compile_definitions(${PROJECT_NAME} PUBLIC
    APP_VERSION="${PROJECT_VERSION}"
    QT_DISABLE_DEPRECATED_BEFORE=0x060500
    RC_ICONS="images/icon.ico"
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Network
    Qt::Widgets
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
    INTERPROCEDURAL_OPTIMIZATION TRUE
)
