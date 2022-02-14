//
// Created by Xinpeng Liu on 2/14/22.
//

#ifndef GRADEANALYSIS_CONCEPT_H
#define GRADEANALYSIS_CONCEPT_H


#include <iostream>
#include <string>
#include <vector>

#include "UsefulTools.h"

using namespace std;

class Concept {
public:
    Concept(string, double);

    // ======================== Getters ======================== //

    /**
     * @Brief returns a hashed unique ID
     */
    size_t GetId();

    string GetTextbook() { return textbook; }
    int GetChapterId() { return chapterId; }
    string GetChapter() { return chapter; }
    double GetConceptId() { return conceptId; }
    string GetConcept() { return concept; }
    int GetPage() { return page; }

    // ======================== Setters ======================== //

    void SetTextbook(string name) { textbook = name; }
    void SetChapterId(int id) { chapterId = id; }
    void SetChapter(string name) { chapter = name; }
    void SetConceptId(double id) { conceptId = id; }
    void SetConcept(string name) { concept = name; }
    void SetPage(int num) { page = num; }

private:
    string textbook;
    int chapterId;
    string chapter;
    double conceptId;
    string concept;
    int page;

    UsefulTools myTools;
};


#endif //GRADEANALYSIS_CONCEPT_H
