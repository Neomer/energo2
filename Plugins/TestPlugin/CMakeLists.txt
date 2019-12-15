cmake_minimum_required(VERSION 3.9)

project(TestPlugin)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_EXE PluginInfo.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCE_EXE})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

