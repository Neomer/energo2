cmake_minimum_required(VERSION 3.9)

project(SDK_Tests)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_EXE main.cpp Types/Uuid_Tests.cpp Types/Uuid_Tests.h)

include_directories(../SDK)
include_directories(../External/GoogleTest/googletest/include)

add_executable(${PROJECT_NAME} ${SOURCE_EXE})
target_link_libraries(${PROJECT_NAME} gtest gtest_main SDK)

set_target_properties(SDK_Tests PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET SDK_Tests PROPERTY CXX_STANDARD 17)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE_DIR:SDK>/libSDK.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)