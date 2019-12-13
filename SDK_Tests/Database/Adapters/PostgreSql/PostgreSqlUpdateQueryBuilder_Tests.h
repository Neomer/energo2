//
// Created by vinokurov on 13.12.2019.
//

#ifndef ENERGO_POSTGRESQLUPDATEQUERYBUILDER_TESTS_H
#define ENERGO_POSTGRESQLUPDATEQUERYBUILDER_TESTS_H

#include <Database/Adapters/PostgreSql/PostgreSqlUpdateQueryBuilder.h>
#include <Database/Adapters/PostgreSql/PostgreSqlTransformationProvider.h>
#include <gtest/gtest.h>

namespace energo::db::adapters {

class PostgreSqlUpdateQueryBuilder_Tests: public testing::Test {
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

#endif //ENERGO_POSTGRESQLUPDATEQUERYBUILDER_TESTS_H
