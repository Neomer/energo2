cmake_minimum_required(VERSION 3.11)

project(DataServer)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_EXE main.cpp)

find_package(PostgreSQL REQUIRED)
if (NOT ${PostgreSQL_FOUND})
    message("PostrgreSql isn't found!")
else(NOT ${PostgreSQL_FOUND})
    message("PostgreSql version found ${PostgreSQL_VERSION_STRING}")
    include_directories(${PostgreSQL_INCLUDE_DIR})
endif(NOT ${PostgreSQL_FOUND})

include_directories(../SDK)
include_directories(../External/libzmq/include)

add_executable(${PROJECT_NAME} ${SOURCE_EXE})
target_link_libraries(${PROJECT_NAME} SDK ${PostgreSQL_LIBRARIES} libzmq)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

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