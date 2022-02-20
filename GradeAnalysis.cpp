//
// Created by Xinpeng Liu on 2/14/22.
//

#include "GradeAnalysis.h"

Quiz* GradeAnalysis::GetQuizPtr(string courseId, string quizId) {
    size_t hashedId = myTools.Hash(courseId + quizId);
    return myTools.GetPtrById(quizPtrList, hashedId);
}

Question* GradeAnalysis::GetQuestionPtr(string courseId, string quizId,
                                        int questionId) {
    size_t hashedId = myTools.Hash(courseId + quizId + to_string(questionId));
    return myTools.GetPtrById(questionPtrList, hashedId);
}

AnswerSheet* GradeAnalysis::GetAnswerSheetPtr(string courseId, string quizId, int studentId){
    size_t hashedId = myTools.Hash(courseId + quizId + to_string(studentId));
    return myTools.GetPtrById(answerSheetPtrList, hashedId);
}

Student* GradeAnalysis::GetStudentPtr(int studentId){
    size_t hashedId = myTools.Hash(to_string(studentId));
    return myTools.GetPtrById(studentPtrList, hashedId);
}

Concept* GradeAnalysis::GetConceptPtr(string textbook, string conceptId){
    size_t hashedId = myTools.Hash(textbook + conceptId);
    return myTools.GetPtrById(conceptPtrList, hashedId);
}

Concept* GradeAnalysis::GetConceptPtrByName(string textbook, string concept){
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

void GradeAnalysis::AddQuizPtr(Quiz* ptr){
    myTools.AddPtrToList(quizPtrList, ptr);
}

void GradeAnalysis::AddQuestionPtr(Question* ptr){
    myTools.AddPtrToList(questionPtrList, ptr);
}

void GradeAnalysis::AddAnswerSheetPtr(AnswerSheet* ptr){
    myTools.AddPtrToList(answerSheetPtrList, ptr);
}

void GradeAnalysis::AddStudentPtr(Student* ptr){
    myTools.AddPtrToList(studentPtrList, ptr);
}

void GradeAnalysis::AddConceptPtr(Concept* ptr){
    myTools.AddPtrToList(conceptPtrList, ptr);
}

void GradeAnalysis::LoadOneQuiz(string folderPath) {

    // Read from txt files
    ReadHelper helper;
    helper.ReadAll(folderPath);
    Quiz* quizPtr = new Quiz(helper.courseId, helper.quizId);

    // Load if the Quiz not exist
    if(!myTools.JudgePtrInList(quizPtrList, quizPtr)) {

        // Initialize Quiz object and add to vector
        quizPtr->SetQuestionAmount(helper.questionAmount);
        quizPtr->SetStudentAmount(helper.studentAmount);
        AddQuizPtr(quizPtr);

        // Initialize Question objects and add them to vector
        for (int i = 0; i < helper.questionAmount; ++i) {
            Question *questionPtr = new Question(helper.courseId, helper.quizId, i + 1, helper.answerKey[i]);
            AddQuestionPtr(questionPtr);
        }

        // Initialize Answer Sheet objects and add them to vector
        for (int i = 0; i < helper.studentAmount; ++i) {
            AnswerSheet *answerSheetPtr = new AnswerSheet(helper.courseId, helper.quizId, helper.studentIds[i]);
            answerSheetPtr->SetQuestionAmount(helper.questionAmount);
            for (int j = 0; j < helper.questionAmount; ++j)
                answerSheetPtr->AddAnswer(helper.studentAnswer[i][j]);
            AddAnswerSheetPtr(answerSheetPtr);
        }

        // Initialize Student objects and add them to vector
        for (int i = 0; i < helper.studentAmount; ++i) {
            Student *studentPtr = new Student(myTools.RandomName(), helper.studentIds[i]);
            AddStudentPtr(studentPtr);
        }

        // Initialize Concept objects and add them to vector
        for (int i = 0; i < helper.conceptList.size(); ++i) {
            Concept *conceptPtr = new Concept(helper.textbook, helper.conceptList[i][3]);

            conceptPtr->SetChapterId(stoi(helper.conceptList[i][1]));
            conceptPtr->SetChapter(helper.conceptList[i][2]);
            conceptPtr->SetConcept(helper.conceptList[i][4]);
            conceptPtr->SetPage(stoi(helper.conceptList[i][5]));

            AddConceptPtr(conceptPtr);
        }

        // Add Question pointers and Answer Sheet pointers to Quiz
        Quiz *theQuizPtr = GetQuizPtr(helper.courseId, helper.quizId);
        for(int i=0; i<helper.questionAmount; ++i)
            theQuizPtr->AddQuestionPtr(GetQuestionPtr(helper.courseId, helper.quizId, i+1));
        for(int i=0; i<helper.studentAmount; ++i)
            theQuizPtr->AddAnswerSheetPtr(GetAnswerSheetPtr(helper.courseId, helper.quizId, helper.studentIds[i]));

        // Add Concept pointers to Question
        for (int i = 0; i < helper.mapQuestionConcept.size(); ++i) {

            vector<string> aMap = helper.mapQuestionConcept[i];
            int questionId = stoi(aMap[0]);
            string concept = aMap[1];

            Question *aQuestion = GetQuestionPtr(helper.courseId, helper.quizId, questionId);
            Concept *aConcept = GetConceptPtrByName(helper.textbook, concept);

            aQuestion->AddConceptPtr(aConcept);
            aQuestion->UpdateConceptAmount();   // update the tracker ("num of concepts" in this Question)
        }

        // Add Question pointers to Answer Sheet objects
       for(int i=0; i<helper.studentAmount; ++i)
       {
           AnswerSheet* aAnswerSheetPtr = GetAnswerSheetPtr(helper.courseId, helper.quizId, helper.studentIds[i]);
           for(int j=0; j<helper.questionAmount; ++j)
           {
               aAnswerSheetPtr->AddQuestionPtr(GetQuestionPtr(helper.courseId, helper.quizId, j+1));
           }
       }

        // Add Answer Sheet pointers to Student
        for(int i=0; i<helper.studentAmount; ++i){
            Student* aStudentPtr = GetStudentPtr(helper.studentIds[i]);
            int studentId = aStudentPtr->GetStudentId();
            AnswerSheet* aAnswerSheetPtr = GetAnswerSheetPtr(helper.courseId, helper.quizId, studentId);
            aStudentPtr->AddAnswerSheetPtr(aAnswerSheetPtr);
        }
    }
    else
    {
        cout << "Can't add the quiz. The Quiz " + quizPtr->GetCourseId() + "-" + quizPtr->GetQuizId() + " exists" << endl;
    }
}

//void GradeAnalysis::GradeOneQuiz(string courseId, string quizId){
//    Quiz* quizPtr = GetQuizPtr(courseId, quizId);
//
//
//}


