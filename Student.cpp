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
    for (int i = 0; i < answerSheetPtrList.size(); ++i) {
        if (answerSheetPtrList[i]->GetId() == hashedId)
            return answerSheetPtrList[i];
    }
    cout << "AnswerSheet not found" << endl;
    return nullptr;
}

void Student::AddAnswerSheetPtr(AnswerSheet* ptr) {
    bool judge = myTools.JudgePtrInList(answerSheetPtrList, ptr);
    if (!judge)
        answerSheetPtrList.push_back(ptr);
    else
        cout << "The AnswerSheet is already exist" << endl;
}
