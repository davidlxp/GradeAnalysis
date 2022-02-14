//
// Created by Xinpeng Liu on 2/14/22.
//

#include "ReadHelper.h"

void ReadHelper ::ReadQuizInfo(string quizInfoPath) {
    string line;
    ifstream file1(quizInfoPath);

    if (file1.is_open()) {
        getline(file1, line);

        vector<string> tempList;
        tempList = myTools.SplitString(line, " ");

        // Save course ID
        courseId = tempList[0];

        // Save quiz ID
        quizId = tempList[tempList.size() - 1];

        file1.close();
    } else
        cout << "Unable to open the file: "
             << "\n"
             << quizInfoPath;
    return;
}

void ReadHelper ::ReadStudentAnswer(string stuAnswerPath) {
    string line;
    ifstream file1(stuAnswerPath);

    if (file1.is_open()) {
        int tracker = 1;  // track which line we are reading
        while (getline(file1, line)) {
            // Store answers to a temporary list
            vector<string> tempList;
            tempList = myTools.SplitString(line, ",");

            // Things to do when it's the 1st line
            if (tracker == 1) {
                // Save students ID
                for (string s : tempList) {
                    studentIds.push_back(stoi(s));
                }

                // Save student amount
                studentAmount = tempList.size();

                // Create N vectors if there're N students
                for (int i = 0; i < studentAmount; ++i) {
                    vector<string> l;
                    studentAnswer.push_back(l);
                }
            } else {
                // Save student answers
                for (int i = 0; i < studentAmount; ++i) {
                    studentAnswer[i].push_back(tempList[i]);
                }
            }
            tracker++;
        }
        file1.close();
    } else
        cout << "Unable to open the file: "
             << "\n"
             << stuAnswerPath;
    return;
}

void ReadHelper ::ReadAnswerKey(string answerKeyPath) {
    string line;
    ifstream file1(answerKeyPath);

    if (file1.is_open()) {
        while (getline(file1, line)) {
            // Save answer keys
            answerKey.push_back(line);

            // Save question amount
            questionAmount++;
        }
        file1.close();
    } else
        cout << "Unable to open the file: "
             << "\n"
             << answerKeyPath;
    return;
}

void ReadHelper ::ReadMap(string mapPath) {
    string line;
    ifstream file1(mapPath);

    if (file1.is_open()) {
        // skip the 1st line
        getline(file1, line);

        while (getline(file1, line)) {
            vector<string> tempList;
            tempList = myTools.SplitString(line, " ");

            // Save relation pairs between questions and concepts
            vector<string> l;
            l.push_back(tempList[0]);
            l.push_back(
                    myTools.CombineStrings(tempList, 1, tempList.size() - 1, " "));
            mapQuestionConcept.push_back(l);
        }
        file1.close();
    } else
        cout << "Unable to open the file: "
             << "\n"
             << mapPath;
    return;
}

void ReadHelper ::ReadConcept(string conceptPath) {
    string line;
    ifstream file1(conceptPath);

    if (file1.is_open()) {
        string currChapterId;
        string currChapter;

        // track which line we are reading
        int tracker = 1;

        while (getline(file1, line)) {
            vector<string> tempList;
            tempList = myTools.SplitString(line, " ");

            if (tracker == 1) {
                // Save textbook name
                textbook = myTools.CombineStrings(tempList, 1, tempList.size() - 1, " ");
            } else if (tempList[0] == "CHAPTER") {
                currChapterId = tempList[1];
                currChapter =
                        myTools.CombineStrings(tempList, 2, tempList.size() - 2, " ");
            } else {
                // Save concept
                vector<string> l;
                l.push_back(textbook);
                l.push_back(currChapterId);
                l.push_back(currChapter);
                l.push_back(tempList[0]);  // concept ID
                l.push_back(myTools.CombineStrings(tempList, 1, tempList.size() - 2,
                                                   " "));    // concept
                l.push_back(tempList[tempList.size() - 1]);  // page
                conceptList.push_back(l);
            }
        }
        file1.close();
    } else
        cout << "Unable to open the file: "
             << "\n"
             << conceptPath;
    return;
}

void ReadHelper ::ReadAll(string folderPath) {
    // Generate all the paths
    string quizInfoPath = folderPath + "/QuizInfo.txt";
    string stuAnswerPath = folderPath + "/StudentAnswer.txt";
    string answerKeyPath = folderPath + "/AnswerKey.txt";
    string mapPath = folderPath + "/MapQuestionConcept.txt";
    string conceptPath = folderPath + "/ConceptList.txt";

    // Call functions to read all files
    ReadQuizInfo(quizInfoPath);
    ReadStudentAnswer(stuAnswerPath);
    ReadAnswerKey(answerKeyPath);
    ReadMap(mapPath);
    ReadConcept(conceptPath);
}
