cmake_minimum_required(VERSION 3.9)

project(HashGen)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_EXE main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_EXE})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

