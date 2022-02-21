#include <iostream>
#include "UsefulTools.h"
#include "Student.h"
#include "ReadHelper.h"
#include "GradeAnalysis.h"

using namespace std;

int main() {

    GradeAnalysis gradeAnalysis;
//    gradeAnalysis.LoadOneQuiz("Files");
    gradeAnalysis.LoadOneQuiz("../Files");
    gradeAnalysis.AnalyzeOneQuiz("csc27774", "quiz1");

    string xx = "Pointers as Function Parameters";







    return 0;
}
