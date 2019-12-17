cmake_minimum_required(VERSION 3.9)

project(TestPlugin)

include_directories(../../SDK)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_EXE PluginInfo.cpp FakeDatabaseAdapter.cpp FakeDatabaseAdapter.h FakeTransformationProvider.cpp FakeTransformationProvider.h FakeConnectionProvider.cpp FakeConnectionProvider.h)

add_library(${PROJECT_NAME} SHARED ${SOURCE_EXE})

target_link_libraries(${PROJECT_NAME} SDK)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

