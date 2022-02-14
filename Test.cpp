//
// Created by Xinpeng Liu on 2/14/22.
//

#include "Test.h"

Test::Test(string textbook1, string course1) {
    textbook = textbook1;
    course = course1;
}

size_t Test::GetId() {
    string original = textbook + course;
    size_t hashedId = myTools.Hash(original);
    return hashedId;
}
