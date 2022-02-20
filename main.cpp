#include <iostream>
#include "UsefulTools.h"
#include "Student.h"
#include "ReadHelper.h"
#include "GradeAnalysis.h"

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;


//    ReadHelper helper;
//    helper.ReadAll("../Files");
//    cout << helper.conceptList.size() << endl;
//    cout << helper.mapQuestionConcept.size() << endl;
//    cout << helper.studentAnswer.size() << endl;
//    cout << helper.answerKey.size() << endl;

    GradeAnalysis gradeAnalysis;
    gradeAnalysis.LoadOneQuiz("../Files");








    return 0;
}
