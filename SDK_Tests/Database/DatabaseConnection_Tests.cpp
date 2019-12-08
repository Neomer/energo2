#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by kir on 07.12.2019.
//

#include "DatabaseConnection_Tests.h"
#include <Database/DatabaseUnavailableException.h>
#include <Database/DatabaseConnectionIsClosedException.h>

using namespace std;
using namespace energo::db;
using namespace energo::exceptions;

TEST_F(DatabaseConnection_Tests, DatabaseUnavailableExceptionOnIncorrectConnectionSettings) {
    random_device rd;
    DatabaseConnectionSettings settings;
    settings.setHost("dffdfd");
    
    DatabaseConnection connection(rd, settings);
    EXPECT_THROW(connection.open(), DatabaseUnavailableException);
}

TEST_F(DatabaseConnection_Tests, NewConnectionMustBeClosed) {
    random_device rd;
    DatabaseConnectionSettings settings;
    DatabaseConnection connection(rd, settings);
    EXPECT_FALSE(connection.isOpen());
}

TEST_F(DatabaseConnection_Tests, ClosingOfClosedConnectionMustNotThrowsAnyExceptions) {
    random_device rd;
    DatabaseConnectionSettings settings;
    DatabaseConnection connection(rd, settings);
    EXPECT_NO_THROW(connection.close());
}

TEST_F(DatabaseConnection_Tests, ClosingAfterFailedConnectionMustNotThrowsAnyExceptions) {
    random_device rd;
    DatabaseConnectionSettings settings;
    DatabaseConnection connection(rd, settings);
    try {
        connection.open();
    } catch (DatabaseUnavailableException &) {
    
    }
    EXPECT_NO_THROW(connection.close());
}

TEST_F(DatabaseConnection_Tests, TwoDifferentConnectionsMustHasDifferentUids) {
    random_device rd;
    DatabaseConnectionSettings settings;
    
    DatabaseConnection connection1(rd, settings),
        connection2(rd, settings);
    
    EXPECT_NE(connection1.getUid(), connection2.getUid());
}

TEST_F(DatabaseConnection_Tests, ExecutionOnClosedConnectionMustThrowException) {
    random_device rd;
    DatabaseConnectionSettings settings;
    DatabaseConnection connection(rd, settings);
    
    EXPECT_THROW(connection.exec(""), DatabaseConnectionIsClosedException);
}

#pragma clang diagnostic pop