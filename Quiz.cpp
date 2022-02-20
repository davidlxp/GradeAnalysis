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
    myTools.AddPtrToList(questionPtrList, ptr);
}

void Quiz ::AddAnswerSheetPtr(AnswerSheet* ptr) {
    myTools.AddPtrToList(answerSheetPtrList, ptr);
}
