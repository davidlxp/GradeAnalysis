//
// Created by Xinpeng Liu on 2/14/22.
//

#ifndef GRADEANALYSIS_QUESTION_H
#define GRADEANALYSIS_QUESTION_H


#include <iostream>
#include <string>
#include <vector>

#include "Concept.h"
#include "UsefulTools.h"

using namespace std;

class Question {
public:
    Question(string, string, int, string);

    // ======================== Getters ======================== //

    /**
     * @Brief returns a hashed unique ID
     */
    size_t GetId();

    string GetCourseId() { return courseId; }
    string GetQuizId() { return quizId; }
    int GetQuestionId() { return questionId; }
    string GetAnswerKey() { return answerKey; }
    int GetConceptAmount() { return conceptAmount; }
    Concept* GetConceptPtr(int index) { return conceptPtrList[index]; }
    bool ConceptExist(Concept* ptr) { return myTools.JudgePtrInList(conceptPtrList, ptr); }

    // ======================== Setters ======================== //

    void SetCourseId(string id) { courseId = id; }
    void SetQuizId(string id) { quizId = id; }
    void SetQuestionId(int id) { questionId = id; }
    void SetAnswerKey(string key) { answerKey = key; }
    void UpdateConceptAmount() { conceptAmount = conceptPtrList.size(); }

    /**
     * @Brief add Concept pointer to the list
     */
    void AddConceptPtr(Concept* ptr);

private:
    string courseId;
    string quizId;
    int questionId = -1;

    string answerKey;
    int conceptAmount = 0;

    // A list of concepts tested in this question
    vector<Concept*> conceptPtrList;

    UsefulTools myTools;
};


#endif //GRADEANALYSIS_QUESTION_H
