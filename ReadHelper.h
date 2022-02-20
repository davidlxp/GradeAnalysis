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
    int studentAmount = 0;
    int questionAmount = 0;

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

//    /**
//     * @Brief Temporary function to check if reading successful
//     */
//     void PrintDVector(vector<vector<string> > vec){
//         for(int i=0; i<vec.size(); ++i)
//         {
//             for(int j=0; j<vec[i].size(); ++j){
//                 cout << vec[i][j];
//                 cout << " | ";
//             }
//             cout << endl;
//         }
//     }

};


#endif //GRADEANALYSIS_READHELPER_H
