//
// Created by Xinpeng Liu on 2/14/22.
//

#ifndef GRADEANALYSIS_GRADEANALYSIS_H
#define GRADEANALYSIS_GRADEANALYSIS_H


#include <iostream>
#include <string>
#include <vector>

#include "AnswerSheet.h"
#include "Concept.h"
#include "Question.h"
#include "Quiz.h"
#include "ReadHelper.h"
#include "Student.h"
#include "UsefulTools.h"

using namespace std;

class GradeAnalysis {
public:
    GradeAnalysis();

    // ======================== Getters ======================== //

    Quiz* GetQuizPtr(string courseId, string quizId);
    Question* GetQuestionPtr(string courseId, string quizId, int questionId);
    AnswerSheet* GetAnswerSheetPtr(string courseId, string quizId, int studentId);
    Student* GetStudentPtr(int studentId);

    /**
     * @Brief two overloaded "GetConceptPtr" functions
     */
    Concept* GetConceptPtr(string textbook, double conceptId);
    Concept* GetConceptPtr(string textbook, string concept);

    // ======================== Setters ======================== //

    void AddQuizPtr(Quiz* ptr);
    void AddQuestionPtr(Question* ptr);
    void AddAnswerSheetPtr(AnswerSheet* ptr);
    void AddStudentPtr(Student* ptr);
    void AddConceptPtr(Concept* ptr);

    // =================== Loader & Analyzer =================== //

    /**
     * @Brief load all the information from files for one quiz
     */
    void LoadOneQuiz(string folderPath);

    /**
     * @Brief grade all the student answers for one quiz
     */
    void GradeOneQuiz(string courseId, string quizId);

    /**
     * @Brief providing analysis report for one quiz
     */
    void AnalyzeOneQuiz(string courseId, string quizId);

private:
    ReadHelper helper;
    vector<Concept*> conceptPtrList;
    vector<Quiz*> quizPtrList;
    vector<Question*> questionPtrList;
    vector<Student*> studentPtrList;
    vector<AnswerSheet*> answerSheetPtrList;

    UsefulTools myTools;
};


#endif //GRADEANALYSIS_GRADEANALYSIS_H
