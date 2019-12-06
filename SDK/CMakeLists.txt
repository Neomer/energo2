cmake_minimum_required(VERSION 3.9)
add_compile_definitions(SDK_EXPORT)

project(SDK)

include_directories(../External/fmtlib/include)

set(SOURCE_EXE global.h Types/Uuid.cpp Types/Uuid.h)

add_library(${PROJECT_NAME} SHARED ${SOURCE_EXE})

target_link_libraries(${PROJECT_NAME} fmt)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)