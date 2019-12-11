//
// Created by kir on 10.12.2019.
//

#include "PostgreSqlTransformationProvider_Tests.h"

using namespace std;
using namespace energo::db::adapters;

TEST_F(PostgreSqlTransformationProvider_Tests, TableNameMustBeQuoted) {
    EXPECT_EQ(provider->EscapeTableNameIfNeeded("SomeName"), "\"SomeName\"");
}


TEST_F(PostgreSqlTransformationProvider_Tests, FieldNameMustBeQuoted) {
    EXPECT_EQ(provider->EscapeTableNameIfNeeded("SomeName"), "\"SomeName\"");
}