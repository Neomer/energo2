//
// Created by vinokurov on 13.12.2019.
//

#ifndef ENERGO_POSTGRESQLDELETEQUERYBUILDER_TESTS_H
#define ENERGO_POSTGRESQLDELETEQUERYBUILDER_TESTS_H

#include <Database/Adapters/PostgreSql/PostgreSqlTransformationProvider.h>
#include <Database/Adapters/PostgreSql/PostgreSqlDeleteQueryBuilder.h>
#include <Database/SqlConditionBuilder.h>
#include <gtest/gtest.h>

namespace energo::db::adapters {

class PostgreSqlDeleteQueryBuilder_Tests: public testing::Test {
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

#endif //ENERGO_POSTGRESQLDELETEQUERYBUILDER_TESTS_H
