//
// Created by Xinpeng Liu on 2/14/22.
//

#ifndef GRADEANALYSIS_ANSWERSHEET_H
#define GRADEANALYSIS_ANSWERSHEET_H


#include <iostream>
#include <string>
#include <vector>

#include "Question.h"
#include "UsefulTools.h"
using namespace std;

class AnswerSheet {
public:
    AnswerSheet(string, string, int);

    // ======================== Getters ======================== //

    /**
     * @Brief return a hashed unique ID for this AnswerSheet object
     */
    size_t GetId();

    string GetCourseId() { return courseId; }
    string GetQuizId() { return quizId; }
    int GetStudentId() { return studentId; }
    string GetAnswer(int index) { return studentAnswer[index]; }
    bool GetGradedAnswer(int index) { return gradedAnswer[index]; }
    int GetErrorNum() { return errorNum; }
    double GetErrorRate() { return errorRate; }
    int GetQuestionAmount() { return questionAmount; }

    /**
     * @Brief get Question ptr by index (eg. questionId=1 at index 0)
     */
    Question* GetQuestionPtr(int index) {
        return questionPtrList[index];
    }

    // ======================== Setters ======================== //

    void SetCourseId(string id) { courseId = id; }
    void SetQuizId(string id) { quizId = id; }
    void SetStudentId(int id) { studentId = id; }
    void AddAnswer(string answer) { studentAnswer.push_back(answer); }
    void AddGradedAnswer(bool answer) { gradedAnswer.push_back(answer); }
    void SetErrorNum(int num) { errorNum = num; }
    void SetErrorRate(double rate) { errorRate = rate; }
    void SetQuestionAmount(int amount) { questionAmount = amount; }

    /**
     * @Brief add Question pointer to the list
     */
    void AddQuestionPtr(Question* ptr);

private:
    string courseId;
    string quizId;
    int studentId = -1;

    int errorNum = 0;
    double errorRate = 0;
    int questionAmount = 0;

    vector<string> studentAnswer;
    vector<bool> gradedAnswer;
    vector<Question*> questionPtrList;

    UsefulTools myTools;
};


#endif //GRADEANALYSIS_ANSWERSHEET_H
