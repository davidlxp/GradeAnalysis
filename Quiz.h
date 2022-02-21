//
// Created by Xinpeng Liu on 2/14/22.
//

#ifndef GRADEANALYSIS_QUIZ_H
#define GRADEANALYSIS_QUIZ_H


#include <iostream>
#include <string>
#include <vector>

#include "AnswerSheet.h"
#include "UsefulTools.h"

class Quiz {
public:
    Quiz(string, string);

    // ======================== Getters ======================== //

    /**
     * @Brief returns a hashed unique ID
     */
    size_t GetId();

    string GetCourseId() { return courseId; }
    string GetQuizId() { return quizId; }
    int GetQuestionAmount() { return questionAmount; }
    int GetStudentAmount() { return studentAmount; }
    int GetConceptAmount() { return conceptAmount; }
    Question* GetQuestionPtr(int index) { return questionPtrList[index]; }
    AnswerSheet* GetAnswerSheetPtr(int index) { return answerSheetPtrList[index]; }
    Concept* GetConceptPtr(int index) { return conceptPtrList[index]; }
    bool ConceptExist(Concept* ptr){ return myTools.JudgePtrInList(conceptPtrList, ptr); }

    // ======================== Setters ======================== //

    void SetCourseId(string id) { courseId = id; }
    void SetQuizId(string id) { quizId = id; }
    void SetQuestionAmount(int amount) { questionAmount = amount; }
    void SetStudentAmount(int amount) { studentAmount = amount; }
    void UpdateConceptAmount() { conceptAmount = conceptPtrList.size(); }

    /**
     * @Brief add a Question pointer to the list
     */
    void AddQuestionPtr(Question* ptr);

    /**
     * @Brief add a Answer Sheet pointer to the list
     */
    void AddAnswerSheetPtr(AnswerSheet* ptr);

    /**
     * @Brief add a Answer Sheet pointer to the list
     */
    void AddConceptPtr(Concept* ptr);



private:
    string courseId;
    string quizId;

    int questionAmount = 0;
    int studentAmount = 0;
    int conceptAmount = 0;

    vector<Question*> questionPtrList;
    vector<AnswerSheet*> answerSheetPtrList;
    vector<Concept*> conceptPtrList;

    UsefulTools myTools;
};


#endif //GRADEANALYSIS_QUIZ_H
