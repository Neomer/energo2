cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_EXE main.cpp)

include_directories(../SDK)

add_executable(Configurator ${SOURCE_EXE})
target_link_libraries(Configurator SDK)

set_target_properties(Configurator PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET Configurator PROPERTY CXX_STANDARD 17)

install(TARGETS Configurator RUNTIME DESTINATION bin)