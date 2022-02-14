//
// Created by Xinpeng Liu on 2/14/22.
//

#ifndef GRADEANALYSIS_READHELPER_H
#define GRADEANALYSIS_READHELPER_H


#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "UsefulTools.h"
using namespace std;

class ReadHelper {
public:
    UsefulTools myTools;

    string textbook;
    string courseId;
    string quizId;
    vector<int> studentIds;
    int studentAmount;
    int questionAmount;

    vector<vector<string> > studentAnswer;
    vector<string> answerKey;
    vector<vector<string> > mapQuestionConcept;
    vector<vector<string> > conceptList;

    /**
     * @Brief read QuizInfo.txt file
     */
    void ReadQuizInfo(string quizInfoPath);

    /**
     * @Brief read StudentAnswer.txt file
     */
    void ReadStudentAnswer(string stuAnswerPath);

    /**
     * @Brief read StudentAnswer.txt file
     */
    void ReadAnswerKey(string answerKeyPath);

    /**
     * @Brief read the map of question-concept relation
     */
    void ReadMap(string mapPath);

    /**
     * @Brief read ConceptList.txt file
     */
    void ReadConcept(string conceptPath);

    /**
     * @Brief read all the txt files
     */
    void ReadAll(string folderPath);
};


#endif //GRADEANALYSIS_READHELPER_H
