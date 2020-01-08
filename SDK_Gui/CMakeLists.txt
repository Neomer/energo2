cmake_minimum_required(VERSION 3.14)

project(SDK_GUI)

include_directories( ../SDK )

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)
include_directories( ${GTKMM_INCLUDE_DIRS} )
link_directories(${GTKMM_LIBRARY_DIRS})

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_EXE Widgets/Window.h Widgets/Window.cpp Widgets/Widget.cpp Widgets/Widget.h Widgets/ToolBar.cpp Widgets/ToolBar.h Widgets/ActionBar.cpp Widgets/ActionBar.h Widgets/StatusBar.cpp Widgets/StatusBar.h Widgets/ActionItem.cpp Widgets/ActionItem.h Widgets/TextActionItem.cpp Widgets/TextActionItem.h Widgets/Layout.cpp Widgets/Layout.h Widgets/VerticalLayout.cpp Widgets/VerticalLayout.h Widgets/Button.cpp Widgets/Button.h ViewModels/Menu.cpp ViewModels/Menu.h ViewModels/MenuItem.cpp ViewModels/MenuItem.h Widgets/IconButton.cpp Widgets/IconButton.h Widgets/TextBox.cpp Widgets/TextBox.h)

add_library(${PROJECT_NAME} SHARED ${SOURCE_EXE})

target_link_libraries(${PROJECT_NAME} SDK ${GTKMM_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if (WIN32)
    set(LibExt dll)
endif (WIN32)

if (UNIX)
    set(LibExt so)
endif (UNIX)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:SDK>/libSDK.${LibExt}"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
