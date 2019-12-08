cmake_minimum_required(VERSION 3.9)
add_compile_definitions(SDK_EXPORT)

project(SDK)

include_directories(../External/fmtlib/include)
include_directories(../External/date/include)
find_package(PostgreSQL REQUIRED)
if (NOT ${PostgreSQL_FOUND})
    message("PostrgreSql isn't found!")
else(NOT ${PostgreSQL_FOUND})
    message("PostgreSql version" + ${PostgreSQL_VERSION_STRING})
    include_directories(${PostgreSQL_INCLUDE_DIRS})
endif(NOT ${PostgreSQL_FOUND})

set(SOURCE_EXE global.h Types/Uuid.cpp Types/Uuid.h Database/SqlQuery.cpp Database/SqlQuery.h Database/DatabaseConnection.cpp Database/DatabaseConnection.h Database/DatabaseConnectionSettings.cpp Database/DatabaseConnectionSettings.h Database/DatabaseUnavailableException.cpp Database/DatabaseUnavailableException.h Database/DatabaseConnectionIsClosedException.cpp Database/DatabaseConnectionIsClosedException.h Database/SqlValue.cpp Database/SqlValue.h Database/SqlQueryBadResultException.cpp Database/SqlQueryBadResultException.h Database/Managers/DataManager.cpp Database/Managers/DataManager.h Database/Model/Data.cpp Database/Model/Data.h Types/DateTime.cpp Types/DateTime.h)

add_library(${PROJECT_NAME} SHARED ${SOURCE_EXE})

target_link_libraries(${PROJECT_NAME} fmt ${PostgreSQL_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)