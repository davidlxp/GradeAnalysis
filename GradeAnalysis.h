//
// Created by Xinpeng Liu on 2/14/22.
//

#ifndef GRADEANALYSIS_GRADEANALYSIS_H
#define GRADEANALYSIS_GRADEANALYSIS_H


#include <iostream>
#include <string>
#include <vector>
#include <map>

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

    /**
     * @Brief two different function to get Quiz pointers
     */
    Quiz* GetQuizPtr(string courseId, string quizId);
    Quiz* GetQuizPtr(int index) { return quizPtrList[index]; }

    Question* GetQuestionPtr(string courseId, string quizId, int questionId);
    AnswerSheet* GetAnswerSheetPtr(string courseId, string quizId, int studentId);
    Student* GetStudentPtr(int studentId);

    /**
     * @Brief two different function to get Concept pointers
     */
    Concept* GetConceptPtr(string, string);
    Concept* GetConceptPtrByName(string, string);

    int GetQuizAmount() { return quizPtrList.size(); }
    int GetQuestionAmount() { return questionPtrList.size(); }
    int GetAnswerSheetAmount() { return answerSheetPtrList.size(); }
    int GetStudentAmount() { return studentPtrList.size(); }

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
     * @Brief functions for initialize objects in GradeAnalysis
     */
    void InitQuiz(ReadHelper&);
    void InitQuestion(ReadHelper&);
    void InitAnswerSheet(ReadHelper&);
    void InitStudent(ReadHelper&);
    void InitConcept(ReadHelper&);

    /**
     * @Brief functions for adding pointer links to a type of objects
     * @Note Please make sure running LinkQuestion before running LinkQuiz
     */
     void LinkQuestion(ReadHelper&);
     void LinkQuiz(ReadHelper&);
     void LinkAnswerSheet(ReadHelper&);
     void LinkStudent(ReadHelper&);

    /**
     * @Brief grade all the student answers for one quiz
     */
    void GradeOneQuiz(string, string);

    /**
     * @Brief functions for providing various of analysis
     */
    void BasicAnalysis(string, string);
    void AnalyzeConcept(string, string);
    void AnalyzeStudent(string, string);
    void AnalyzeQuestion(string, string);

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
