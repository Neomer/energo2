//
// Created by kir on 10.12.2019.
//

#include "DatabaseQueryBuilder.h"

using namespace std;
using namespace energo::db;

DatabaseQueryBuilder::DatabaseQueryBuilder(const TransformationProvider &provider):
    _provider{provider}
{

}
