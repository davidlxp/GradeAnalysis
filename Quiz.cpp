//
// Created by Xinpeng Liu on 2/14/22.
//

#include "Quiz.h"

Quiz ::Quiz(string courseId1, string quizId1) {
    courseId = courseId1;
    quizId = quizId1;
}

size_t Quiz ::GetId() {
    string originalId = courseId + quizId;
    size_t hashedId = myTools.Hash(originalId);
    return hashedId;
}

void Quiz ::AddQuestionPtr(Question* ptr) {
    bool judge = myTools.JudgePtrInList(questionPtrList, ptr);
    if (!judge)
        questionPtrList.push_back(ptr);
    else
        cout << "The Question is already exist" << endl;
}

void Quiz ::AddAnswerSheetPtr(AnswerSheet* ptr) {
    bool judge = myTools.JudgePtrInList(answerSheetPtrList, ptr);
    if (!judge)
        answerSheetPtrList.push_back(ptr);
    else
        cout << "The Answer Sheet is already exist" << endl;
}
