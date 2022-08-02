cmake_minimum_required(VERSION 3.16)
project(UndertaleSaveEditor VERSION 2.0.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Network Widgets)

qt6_add_executable(UndertaleSaveEditor WIN32 MACOSX_BUNDLE
    src/core/dialogs.cpp src/core/dialogs.h
    src/core/initools.cpp src/core/initools.h
    src/core/mainwindow.cpp src/core/mainwindow.h
    src/core/pages.cpp src/core/pages.h
    src/core/tools.cpp src/core/tools.h
    src/filedownloader.h
    src/helpers.h
    src/main.cpp
)

target_compile_definitions(UndertaleSaveEditor PUBLIC
	APP_VERSION="2.0.0.0"
    QT_DISABLE_DEPRECATED_BEFORE=0x060000
	RC_ICONS="images/icon.ico"
	CONFIG+=c++20
)

target_link_libraries(UndertaleSaveEditor PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Network
    Qt::Widgets
)

# Resources:
set_source_files_properties("fonts/Vegur-Regular.otf"
    PROPERTIES QT_RESOURCE_ALIAS "common-font"
)
set_source_files_properties("images/ico_debug.png"
    PROPERTIES QT_RESOURCE_ALIAS "menu-debug"
)
set_source_files_properties("images/ico_dogshrine.png"
    PROPERTIES QT_RESOURCE_ALIAS "menu-shrine"
)
set_source_files_properties("images/ico_floppy.png"
    PROPERTIES QT_RESOURCE_ALIAS "saved"
)
set_source_files_properties("images/ico_floppy_red.png"
    PROPERTIES QT_RESOURCE_ALIAS "unsaved"
)
set_source_files_properties("images/ico_froggit.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-froggit"
)
set_source_files_properties("images/ico_napstablook.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-napstablook"
)
set_source_files_properties("images/ico_temmie.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-temmie"
)
set_source_files_properties("images/ico_muffet.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-muffet"
)
set_source_files_properties("images/ico_riverperson.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-riverperson"
)
set_source_files_properties("images/ico_player.png"
    PROPERTIES QT_RESOURCE_ALIAS "menu-player"
)
set_source_files_properties("images/ico_ribbon.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-ribbon"
)
set_source_files_properties("images/ico_fight.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-fight"
)
set_source_files_properties("images/ico_spaghetti.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-spaghetti"
)
set_source_files_properties("images/ico_savepoint.png"
    PROPERTIES QT_RESOURCE_ALIAS "menu-locations"
)
set_source_files_properties("images/ico_flowey.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-flowey"
)
set_source_files_properties("images/ico_toriel.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-toriel"
)
set_source_files_properties("images/ico_sans.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-sans"
)
set_source_files_properties("images/ico_papyrus.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-papyrus"
)
set_source_files_properties("images/ico_undyne.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-undyne"
)
set_source_files_properties("images/ico_alphys.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-alphys"
)
set_source_files_properties("images/ico_mettaton.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-mettaton"
)
set_source_files_properties("images/ico_asgore.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-asgore"
)
set_source_files_properties("images/ico_asriel.png"
	PROPERTIES QT_RESOURCE_ALIAS "menu-asriel"
)
set_source_files_properties("images/icon.png"
    PROPERTIES QT_RESOURCE_ALIAS "icon"
)
set(assets_resource_files
    "fonts/Vegur-Regular.otf"
    "images/ico_debug.png"
    "images/ico_dogshrine.png"
    "images/ico_floppy.png"
    "images/ico_floppy_red.png"
	"images/ico_froggit.png"
	"images/ico_napstablook.png"
	"images/ico_temmie.png"
	"images/ico_muffet.png"
	"images/ico_riverperson.png"
	"images/ico_player.png"
	"images/ico_ribbon.png"
	"images/ico_fight.png"
	"images/ico_spaghetti.png"
    "images/ico_savepoint.png"
	"images/ico_flowey.png"
	"images/ico_toriel.png"
	"images/ico_sans.png"
	"images/ico_papyrus.png"
	"images/ico_undyne.png"
	"images/ico_alphys.png"
	"images/ico_mettaton.png"
	"images/ico_asgore.png"
	"images/ico_asriel.png"
    "images/icon.png"
)

qt6_add_resources(UndertaleSaveEditor "assets"
    PREFIX
        "/"
    FILES
        ${assets_resource_files}
)
