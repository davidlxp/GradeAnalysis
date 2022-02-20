//
// Created by Xinpeng Liu on 2/14/22.
//

#include "Question.h"

Question::Question(string courseId1, string quizId1, int questionId1,
                   string key) {
    courseId = courseId1;
    quizId = quizId1;
    questionId = questionId1;
    answerKey = key;
}

size_t Question ::GetId() {
    string originalId = courseId + quizId + to_string(questionId);
    size_t hashedId = myTools.Hash(originalId);
    return hashedId;
}

void Question ::AddConceptPtr(Concept* ptr) {
    myTools.AddPtrToList(conceptPtrList, ptr);
}

