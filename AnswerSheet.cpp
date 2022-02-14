//
// Created by Xinpeng Liu on 2/14/22.
//

#include "AnswerSheet.h"

using namespace std;

AnswerSheet ::AnswerSheet(string courseId1, string quizId1, int studentId1) {
    courseId = courseId1;
    quizId = quizId1;
    studentId = studentId1;
}

size_t AnswerSheet ::GetId() {
    string originalId = courseId + quizId + to_string(studentId);
    size_t hashedId = myTools.Hash(originalId);
    return hashedId;
}

void AnswerSheet ::AddQuestionPtr(Question *ptr) {
    bool judge = myTools.JudgePtrInList(questionPtrList, ptr);
    if (!judge)
        questionPtrList.push_back(ptr);
    else
        cout << "The Question is already exist" << endl;
}

