//
// Created by Xinpeng Liu on 2/14/22.
//

#include "Student.h"

Student::Student(string name, int id) {
    studentName = name;
    studentId = id;
}

size_t Student::GetId() {
    string originalId = to_string(studentId);
    size_t hashedId = myTools.Hash(originalId);
    return hashedId;
}

AnswerSheet* Student::GetAnswerSheetPtr(string courseId, string quizId,
                                        int studentId) {
    size_t hashedId = myTools.Hash(courseId + quizId + to_string(studentId));
    return myTools.GetPtrById(answerSheetPtrList, hashedId);
}

void Student::AddAnswerSheetPtr(AnswerSheet* ptr) {
    myTools.AddPtrToList(answerSheetPtrList, ptr);
}
