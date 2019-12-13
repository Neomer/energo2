//
// Created by vinokurov on 13.12.2019.
//

#ifndef ENERGO_POSTGRESQLINSERTQUERYBUILDER_TESTS_H
#define ENERGO_POSTGRESQLINSERTQUERYBUILDER_TESTS_H

#include <Database/Adapters/PostgreSql/PostgreSqlTransformationProvider.h>
#include <Database/Adapters/PostgreSql/PostgreSqlInsertQueryBuilder.h>
#include <Database/SqlComparisonBuilder.h>
#include <gtest/gtest.h>

namespace energo::db::adapters {

class PostgreSqlInsertQueryBuilder_Tests: public testing::Test {
protected:
    PostgreSqlTransformationProvider *transformationProvider;

    void SetUp() override {
        Test::SetUp();
        transformationProvider = new PostgreSqlTransformationProvider();
    }

    void TearDown() override {
        delete transformationProvider;
        Test::TearDown();
    }
};

}

#endif //ENERGO_POSTGRESQLINSERTQUERYBUILDER_TESTS_H
