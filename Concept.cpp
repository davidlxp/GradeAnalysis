//
// Created by Xinpeng Liu on 2/14/22.
//

#include "Concept.h"

Concept::Concept(string textbook1, double conceptId1) {
    textbook = textbook1;
    conceptId = conceptId1;
}

size_t Concept::GetId() {
    string originalId = textbook + to_string(conceptId);
    size_t hashedId = myTools.Hash(originalId);
    return hashedId;
}
