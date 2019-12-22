cmake_minimum_required(VERSION 3.9)
add_compile_definitions(SDK_EXPORT)

project(SDK)

include_directories(../External/fmtlib/include)
include_directories(../External/date/include)
find_package(PostgreSQL REQUIRED)
if (NOT ${PostgreSQL_FOUND})
    message("PostrgreSql isn't found!")
else(NOT ${PostgreSQL_FOUND})
    message("PostgreSql version found ${PostgreSQL_VERSION_STRING}")
    include_directories(${PostgreSQL_INCLUDE_DIR})
endif(NOT ${PostgreSQL_FOUND})

set(SOURCE_EXE global.h Types/Uuid.cpp Types/Uuid.h
        Database/SqlQuery.cpp Database/SqlQuery.h
        Database/DatabaseConnection.cpp Database/DatabaseConnection.h
        Database/DatabaseConnectionSettings.cpp Database/DatabaseConnectionSettings.h
        Database/DatabaseUnavailableException.cpp Database/DatabaseUnavailableException.h
        Database/DatabaseConnectionIsClosedException.cpp Database/DatabaseConnectionIsClosedException.h
        Database/SqlValue.cpp Database/SqlValue.h
        Database/SqlQueryBadResultException.cpp Database/SqlQueryBadResultException.h
        Database/Managers/DataManager.cpp Database/Managers/DataManager.h
        Database/Model/Data.cpp Database/Model/Data.h
        Database/Model/User.cpp Database/Model/User.h
        Database/TransformationProvider.cpp Database/TransformationProvider.h
        Database/DatabaseResultAdapter.cpp Database/DatabaseResultAdapter.h
        Database/Model/DatabaseStoredEntity.h Database/Model/DatabaseStoredEntity.cpp
        Types/DateTime.cpp Types/DateTime.h
        Database/SqlQueryReader.h Database/SqlQueryReader.cpp
        Database/Adapters/PostgreSql/PostgreSqlResultAdapter.cpp Database/Adapters/PostgreSql/PostgreSqlResultAdapter.h
        Database/Adapters/PostgreSql/PostgreSqlTransformationProvider.cpp Database/Adapters/PostgreSql/PostgreSqlTransformationProvider.h
        Database/Adapters/PostgreSql/PostgreSqlConnectionAdapter.cpp Database/Adapters/PostgreSql/PostgreSqlConnectionAdapter.h
        Database/SqlQueryBuilder.cpp Database/SqlQueryBuilder.h
        Database/SqlSelectQueryBuilder.cpp Database/SqlSelectQueryBuilder.h
        Database/Adapters/PostgreSql/PostgreSqlSelectQueryBuilder.cpp Database/Adapters/PostgreSql/PostgreSqlSelectQueryBuilder.h
        Database/Adapters/PostgreSql/PostgreSqlQueryBuilder.cpp Database/Adapters/PostgreSql/PostgreSqlQueryBuilder.h
        BenchmarkTimer.h BenchmarkTimer.cpp
        Database/Model/IdentifiedEntity.cpp Database/Model/IdentifiedEntity.h
        Metadata/MetaClass.cpp Metadata/MetaClass.h
        Metadata/MetadataProvider.cpp Metadata/MetadataProvider.h
        BenchmarkTimer.cpp BenchmarkTimer.h
        Metadata/MetaClass.cpp Metadata/MetaClass.h
        Metadata/TypeUids.h
        Metadata/MetadataProvider.cpp Metadata/MetadataProvider.h
        Metadata/ClassMetadata.cpp Metadata/ClassMetadata.h
        Metadata/TypeMetadata.cpp Metadata/TypeMetadata.h
        Database/Managers/UserManager.cpp Database/Managers/UserManager.h
        Database/Managers/EntityManager.cpp Database/Managers/EntityManager.h
        Metadata/EntityMetadata.cpp Metadata/EntityMetadata.h
        Database/DatabaseConnectionProvider.cpp Database/DatabaseConnectionProvider.h
        Database/Adapters/PostgreSql/PostgreSqlConnectionProvider.cpp Database/Adapters/PostgreSql/PostgreSqlConnectionProvider.h
        Database/SqlConditionBuilder.cpp Database/SqlConditionBuilder.h classes.h Database/SqlInsertQueryBuilder.cpp Database/SqlInsertQueryBuilder.h Database/Adapters/PostgreSql/PostgreSqlInsertQueryBuilder.cpp Database/Adapters/PostgreSql/PostgreSqlInsertQueryBuilder.h Database/SqlUpdateQueryBuilder.cpp Database/SqlUpdateQueryBuilder.h Database/Adapters/PostgreSql/PostgreSqlUpdateQueryBuilder.cpp Database/Adapters/PostgreSql/PostgreSqlUpdateQueryBuilder.h Database/SqlDeleteQueryBuilder.cpp Database/SqlDeleteQueryBuilder.h Database/Adapters/PostgreSql/PostgreSqlDeleteQueryBuilder.cpp Database/Adapters/PostgreSql/PostgreSqlDeleteQueryBuilder.h ../Tools/HashGen/main.cpp Plugin/PluginLoader.h Plugin/PluginLoader_linux.cpp Plugin/Plugin.cpp Plugin/Plugin.h Plugin/PluginInfo.h ../Plugins/TestPlugin/PluginInfo.cpp Types/Version.cpp Types/Version.h Plugin/PluginLoader_win.cpp Data/DataProvider.cpp Data/DataProvider.h Database/Patch/Patch.cpp Database/Patch/Patch.h Database/Adapters/PostgreSql/Patches/InitialPatch.cpp Database/Adapters/PostgreSql/Patches/InitialPatch.h Metadata/MetadataRegistrar.cpp Metadata/MetadataRegistrar.h Metadata/SingletonClassMetadata.cpp Metadata/SingletonClassMetadata.h)

add_library(${PROJECT_NAME} SHARED ${SOURCE_EXE})

target_link_libraries(${PROJECT_NAME} fmt ${PostgreSQL_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)