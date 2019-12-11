//
// Created by kir on 08.12.2019.
//

#include <iostream>
#include "DateTime_Tests.h"

using namespace std;
using namespace energo::types;

TEST_F(DateTime_Tests, Sample) {
    DateTime dt;
    DateTime dt1(2015, 3, 2);
    DateTime now = DateTime::Now();
    
    auto s1 = dt.toString();
    auto s2 = dt1.toString();
    auto s3 = now.toString();
    
    cout << s1 << " " << s2 << " " << s3 << endl;
}