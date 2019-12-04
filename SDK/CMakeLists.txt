cmake_minimum_required(VERSION 3.9)
add_compile_definitions(SDK_EXPORT)

set(SOURCE_EXE global.h Types/Uuid.cpp Types/Uuid.h)

add_library(SDK SHARED ${SOURCE_EXE})

set_target_properties(SDK PROPERTIES LINKER_LANGUAGE CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(TARGET SDK PROPERTY CXX_STANDARD 17)

install(TARGETS SDK RUNTIME DESTINATION bin)