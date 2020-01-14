cmake_minimum_required(VERSION 3.9)

project(SDK_Tests)



set(CMAKE_CXX_STANDARD 17)
set(SOURCE_EXE main.cpp
        Types/Uuid_Tests.cpp Types/Uuid_Tests.h
        Database/SqlQuery_Tests.cpp Database/SqlQuery_Tests.h
        Database/DatabaseConnectionSettings_Tests.cpp Database/DatabaseConnectionSettings_Tests.h
        Database/DatabaseConnection_Tests.cpp Database/DatabaseConnection_Tests.h
        Database/SqlValue_Tests.cpp Database/SqlValue_Tests.h
        Types/DateTime_Tests.cpp Types/DateTime_Tests.h
        Database/Adapters/PostgreSql/PostgreSqlTransformationProvider_Tests.cpp Database/Adapters/PostgreSql/PostgreSqlTransformationProvider_Tests.h
        Database/Adapters/PostgreSql/PostgreSqlSelectQueryBuilder_Tests.cpp Database/Adapters/PostgreSql/PostgreSqlSelectQueryBuilder_Tests.h
        Database/SqlComparisonBuilder_Tests.cpp Database/SqlComparisonBuilder_Tests.h
        Database/Adapters/PostgreSql/PostgreSqlInsertQueryBuilder_Tests.cpp Database/Adapters/PostgreSql/PostgreSqlInsertQueryBuilder_Tests.h
        Database/Adapters/PostgreSql/PostgreSqlUpdateQueryBuilder_Tests.cpp Database/Adapters/PostgreSql/PostgreSqlUpdateQueryBuilder_Tests.h
        Database/Adapters/PostgreSql/PostgreSqlDeleteQueryBuilder_Tests.cpp Database/Adapters/PostgreSql/PostgreSqlDeleteQueryBuilder_Tests.h Types/Version_Tests.cpp Types/Version_Tests.h Types/ThreadSafeArray_Tests.cpp Types/ThreadSafeArray_Tests.h Types/ThreadSafeQueue_Tests.cpp Types/ThreadSafeQueue_Tests.h Types/DynamicSizeQueue_Tests.cpp Types/DynamicSizeQueue_Tests.h)

include_directories(../SDK)
include_directories(../External/GoogleTest/googletest/include)
find_package(PostgreSQL REQUIRED)
if (NOT ${PostgreSQL_FOUND})
    message("PostrgreSql isn't found!")
else(NOT ${PostgreSQL_FOUND})
    message("PostgreSql version found ${PostgreSQL_VERSION_STRING}")
    include_directories(${PostgreSQL_INCLUDE_DIR})
endif(NOT ${PostgreSQL_FOUND})

add_executable(${PROJECT_NAME} ${SOURCE_EXE})
target_link_libraries(${PROJECT_NAME} gtest gtest_main fmt SDK ${PostgreSQL_LIBRARIES})

set_target_properties(SDK_Tests PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(TARGET SDK_Tests PROPERTY CXX_STANDARD 17)

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