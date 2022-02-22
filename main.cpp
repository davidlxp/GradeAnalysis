#include <iostream>
#include <string>

#include "GradeAnalysis.h"
#include "UsefulTools.h"
using namespace std;

void PrintMainMenu();
void PrintAnalysisMenu();
void PrintQuizzes(GradeAnalysis&);
void DoAnalysis(GradeAnalysis&, int, int);
void RunProgram();

int main() {

    /* Initialize random seed: */
    srand (time(NULL));

    /* Run Grade Analysis program */
    RunProgram();

    return 0;
}


/**
 * @Brief function prints the Main Menu
 */
void PrintMainMenu(){
    cout << "\n"
         << "Please provide command:" << "\n"
         << "1. Load quiz" << "\n"
         << "2. Analyze quiz" << "\n"
         << "-1. Exit program" << "\n\n"
         << "Selection: ";
}

/**
 * @Brief function prints the Analysis Menu
 */
void PrintAnalysisMenu(){
    cout << "How do you want to analyze the quiz:" << "\n"
         << "1. Full Report" << "\n"
         << "2. Basic statistics" << "\n"
         << "3. Concept analysis" << "\n"
         << "4. Student analysis" << "\n"
         << "5. Question analysis" << "\n"
         << "6. To main menu" << "\n"
         << "Selection: ";
}

/**
 * @Brief prints all quizzes in a GradeAnalysis program
 */
void PrintQuizzes(GradeAnalysis& ga){
    cout << "Please choose a quiz by index:" << endl;
    for(int i=0; i<ga.GetQuizAmount(); ++i){
        Quiz* quizPtr = ga.GetQuizPtr(i);
        string courseId = quizPtr->GetCourseId();
        string quizId = quizPtr->GetQuizId();
        cout << i+1 << ". " << courseId << " " << quizId << endl;
    }
    cout << "\n" << "Selection: ";
}

/**
 * @Brief function to conduct analysis
 */
void DoAnalysis(GradeAnalysis& ga, int quizChoice, int anaChoice){

    /* Validation */
    int quizAmount = ga.GetQuizAmount();
    int anaChoiceMax = 6;
    int anaChoiceMin = 1;
    if(quizChoice > quizAmount ||
        anaChoice < anaChoiceMin || anaChoice > anaChoiceMax)
    {
        cout << "\n" << "Quiz Selection or Analysis Choice is invalid!"
            << "\n" << endl;
        return;
    }

    /* Get Quiz information for analysis */
    Quiz* quizPtr = ga.GetQuizPtr(quizChoice-1);
    string courseId = quizPtr->GetCourseId();
    string quizId = quizPtr->GetQuizId();

    /* Switch function to decide what to do */
    switch(anaChoice){
        case 1:
            ga.AnalyzeOneQuiz(courseId, quizId);
            break;
        case 2:
            ga.BasicAnalysis(courseId, quizId);
            break;
        case 3:
            ga.AnalyzeConcept(courseId, quizId);
            break;
        case 4:
            ga.AnalyzeStudent(courseId, quizId);
            break;
        case 5:
            ga.AnalyzeQuestion(courseId, quizId);
            break;
        case 6:
            break;
    }
}

/**
 * @Brief the core user interface program
 */
void RunProgram(){

    /* Important Initialization */
    UsefulTools myTools;
    GradeAnalysis gradeAnalysis;

    /* Welcome of the program */
    string welcome = "Welcome to the Grade Analysis Program!";
    cout << "\n" << myTools.RepeatString("=",welcome.length()+18) << "\n"
         << myTools.RepeatString(" ",9) << welcome << myTools.RepeatString(" ",9)
         << "\n" << myTools.RepeatString("=",welcome.length()+18) << "\n" << endl;

    /* Run the program */
    int choice = 0;
    while(choice != -1){
        PrintMainMenu();
        cin >> choice;

        if(choice == 1){
            cout << "\n\n"
                 << """(Local IDE) For Demo, please copy and paste:  ../Files""" << endl;
//            cout << """(Replit) For Demo, please copy and paste:  Files""" << endl;

            cout << "Please provide folder path: ";            // Ask user for the folder path
            string folderPath;
            cin >> folderPath;

            gradeAnalysis.LoadOneQuiz(folderPath);            // Load one quiz
        }
        else if(choice == 2){
            int quizAmount = gradeAnalysis.GetQuizAmount();
            if(quizAmount != 0) {
                PrintQuizzes(gradeAnalysis);                   // Print available quizzes
                int quizChoice;
                cin >> quizChoice;                                // User choose what to analyze

                PrintAnalysisMenu();                              // Ask the user how to analyze
                int anaChoice;
                cin >> anaChoice;                                 // Ask the user to provide analysis choice
                cout << "\n" << endl;

                DoAnalysis(gradeAnalysis, quizChoice,          // Provide Analysis
                           anaChoice);
            }
            else
                cout << "\n" << "No quiz available..." << "\n" << endl;
        }
    }

    /* Ending of the program */
    string end = "Thanks for using the program!";
    cout << "\n" << myTools.RepeatString("=",end.length()+18) << "\n"
         << myTools.RepeatString(" ",9) << end << myTools.RepeatString(" ",9)
         << "\n" << myTools.RepeatString("=",end.length()+18) << "\n" << endl;
}

