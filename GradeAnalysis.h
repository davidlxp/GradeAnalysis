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

    // ======================== Getters ======================== //

    Quiz* GetQuizPtr(string courseId, string quizId);
    Question* GetQuestionPtr(string courseId, string quizId, int questionId);
    AnswerSheet* GetAnswerSheetPtr(string courseId, string quizId, int studentId);
    Student* GetStudentPtr(int studentId);

    /**
     * @Brief two different function to get Concept pointers
     */
    Concept* GetConceptPtr(string, string);
    Concept* GetConceptPtrByName(string, string);

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
    void LoadOneQuiz(string);

    /**
     * @Brief grade all the student answers for one quiz
     */
    void GradeOneQuiz(string, string);

    /**
     * @Brief providing analysis report for one quiz
     */
    void AnalyzeOneQuiz(string courseId, string quizId);

private:
    vector<Concept*> conceptPtrList;
    vector<Quiz*> quizPtrList;
    vector<Question*> questionPtrList;
    vector<Student*> studentPtrList;
    vector<AnswerSheet*> answerSheetPtrList;

    UsefulTools myTools;
};


#endif //GRADEANALYSIS_GRADEANALYSIS_H
