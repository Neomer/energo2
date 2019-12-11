//
// Created by kir on 10.12.2019.
//

#ifndef ENERGO_POSTGRESQLSELECTQUERYBUILDER_TESTS_H
#define ENERGO_POSTGRESQLSELECTQUERYBUILDER_TESTS_H

#include <Database/Adapters/PostgreSql/PostgreSqlTransformationProvider.h>
#include <Database/Adapters/PostgreSql/PostgreSqlSelectQueryBuilder.h>
#include <gtest/gtest.h>

namespace energo::db::adapters {


class PostgreSqlSelectQueryBuilder_Tests: public testing::Test {
protected:
    PostgreSqlTransformationProvider *provider;
    
    void SetUp() override {
        Test::SetUp();
        provider = new PostgreSqlTransformationProvider();
    }
    
    void TearDown() override {
        delete provider;
        Test::TearDown();
    }
};

}

#endif //ENERGO_POSTGRESQLSELECTQUERYBUILDER_TESTS_H
