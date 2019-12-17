cmake_minimum_required(VERSION 3.9)

project(UuidParser)

include_directories(../../SDK)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_EXE main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_EXE})

target_link_libraries(${PROJECT_NAME} SDK)

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
