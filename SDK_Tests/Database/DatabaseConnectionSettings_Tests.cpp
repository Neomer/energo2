#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by kir on 07.12.2019.
//

#include "DatabaseConnectionSettings_Tests.h"

using namespace std;
using namespace energo::db;

TEST_F(DatabaseConnectionSettings_Tests, GetAndSetHostMatch) {
    DatabaseConnectionSettings settings;
    settings.setHost("localhost");
    EXPECT_EQ(settings.getHost(), "localhost");
}

TEST_F(DatabaseConnectionSettings_Tests, GetAndSetPortMatch) {
    DatabaseConnectionSettings settings;
    settings.setPort(1024);
    EXPECT_EQ(settings.getPort(), 1024);
}

TEST_F(DatabaseConnectionSettings_Tests, GetAndSetUsernameMatch) {
    DatabaseConnectionSettings settings;
    settings.setUser("postgres");
    EXPECT_EQ(settings.getUser(), "postgres");
}

TEST_F(DatabaseConnectionSettings_Tests, GetAndSetPasswordMatch) {
    DatabaseConnectionSettings settings;
    settings.setPassword("1234");
    EXPECT_EQ(settings.getPassword(), "1234");
}

TEST_F(DatabaseConnectionSettings_Tests, GetAndSetDatabaseNameMatch) {
    DatabaseConnectionSettings settings;
    settings.setDatabase("DbName");
    EXPECT_EQ(settings.getDatabase(), "DbName");
}

#pragma clang diagnostic pop