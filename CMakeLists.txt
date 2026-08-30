cmake_minimum_required(VERSION 3.16)

project(quicknote VERSION 0.1 LANGUAGES CXX)

if(APPLE)
    enable_language(OBJCXX)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(quicknote
    src/main.cpp
    src/dailynote.h
    src/dailynote.cpp
    src/globalhotkey.h
    src/globalhotkey.mm
)

qt_add_qml_module(quicknote
    URI Quicknote
    VERSION 1.0
    QML_FILES
        qml/Main.qml
    RESOURCES
        resources/tray-icon.png
)

target_include_directories(quicknote PRIVATE src)

target_link_libraries(quicknote PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
)

if(APPLE)
    target_link_libraries(quicknote PRIVATE "-framework Carbon")
endif()

if(APPLE)
    target_sources(quicknote PRIVATE resources/AppIcon.icns)
    set_source_files_properties(resources/AppIcon.icns PROPERTIES
        MACOSX_PACKAGE_LOCATION Resources
    )
endif()

set_target_properties(quicknote PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_ICON_FILE AppIcon.icns
)
