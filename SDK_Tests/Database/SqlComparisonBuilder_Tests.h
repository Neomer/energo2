//
// Created by vinokurov on 13.12.2019.
//

#ifndef ENERGO_SQLCOMPARISONBUILDER_TESTS_H
#define ENERGO_SQLCOMPARISONBUILDER_TESTS_H

#include <Database/Adapters/PostgreSql/PostgreSqlTransformationProvider.h>
#include <Database/SqlComparisonBuilder.h>
#include <gtest/gtest.h>

namespace energo::db {

class SqlComparisonBuilder_Tests: public testing::Test {
protected:
    adapters::PostgreSqlTransformationProvider _tp;

    void SetUp() override {
        Test::SetUp();
    }

    void TearDown() override {
        Test::TearDown();
    }
};

}

#endif //ENERGO_SQLCOMPARISONBUILDER_TESTS_H
