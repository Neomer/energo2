//
// Created by kir on 10.12.2019.
//

#include "SqlQueryBuilder.h"

using namespace std;
using namespace energo::db;

SqlQueryBuilder::SqlQueryBuilder(const TransformationProvider &provider):
    _provider{provider}
{

}
