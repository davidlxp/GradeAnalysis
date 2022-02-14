//
// Created by Xinpeng Liu on 2/14/22.
//

#ifndef GRADEANALYSIS_TEST_H
#define GRADEANALYSIS_TEST_H

#include <iostream>
#include <string>
#include <vector>

#include "UsefulTools.h"

using namespace std;

class Test {
public:
    Test(string, string);
    size_t GetId();
private:
    UsefulTools myTools;
    string textbook;
    string course;
};


#endif //GRADEANALYSIS_TEST_H
