//
// Created by Xinpeng Liu on 2/14/22.
//

#include "GradeAnalysis.h"

Quiz* GradeAnalysis::GetQuizPtr(string courseId, string quizId) {
    size_t hashedId = myTools.Hash(courseId + quizId);
    for (int i = 0; i < quizPtrList.size(); ++i) {
        if (quizPtrList[i]->GetId() == hashedId) return quizPtrList[i];
    }
    cout << "Quiz not found" << endl;
    return nullptr;
}

Question* GradeAnalysis::GetQuestionPtr(string courseId, string quizId,
                                        int questionId) {
    size_t hashedId = myTools.Hash(courseId + quizId + to_string(questionId));
    for (int i = 0; i < questionPtrList.size(); ++i) {
        if (questionPtrList[i]->GetId() == hashedId) return questionPtrList[i];
    }
    cout << "Question not found" << endl;
    return nullptr;
}

AnswerSheet* GradeAnalysis::GetAnswerSheetPtr(string courseId, string quizId, int studentId){
    size_t hashedId = myTools.Hash(courseId + quizId + to_string(studentId));
    for (int i = 0; i < answerSheetPtrList.size(); ++i) {
        if (answerSheetPtrList[i]->GetId() == hashedId) return answerSheetPtrList[i];
    }
    cout << "Answer Sheet not found" << endl;
    return nullptr;
}

Student* GradeAnalysis::GetStudentPtr(int studentId){
    size_t hashedId = myTools.Hash(to_string(studentId));
    for (int i = 0; i < studentPtrList.size(); ++i) {
        if (studentPtrList[i]->GetId() == hashedId) return studentPtrList[i];
    }
    cout << "Student not found" << endl;
    return nullptr;
}

Concept* GradeAnalysis::GetConceptPtr(string textbook, double conceptId){
    size_t hashedId = myTools.Hash(textbook + to_string(conceptId));
    for (int i = 0; i < conceptPtrList.size(); ++i) {
        if (conceptPtrList[i]->GetId() == hashedId) return conceptPtrList[i];
    }
    cout << "Concept not found" << endl;
    return nullptr;
}

Concept* GradeAnalysis::GetConceptPtr(string textbook, string concept){
    size_t hashedId = myTools.Hash(textbook + concept);
    for (int i = 0; i < conceptPtrList.size(); ++i) {
        size_t hashedId1 =  myTools.Hash(conceptPtrList[i]->GetTextbook() + conceptPtrList[i]->GetConcept());
        if (hashedId1 == hashedId) {
            return conceptPtrList[i];
        }
    }
    cout << "Concept not found" << endl;
    return nullptr;
}


