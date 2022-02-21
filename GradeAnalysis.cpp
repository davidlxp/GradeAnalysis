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

        // Add Question pointers and Concept pointers to Quiz
        Quiz *theQuizPtr = GetQuizPtr(helper.courseId, helper.quizId);
        for(int i=0; i<helper.questionAmount; ++i)
        {
            /* Add Question pointers */
            Question* questionPtr = GetQuestionPtr(helper.courseId, helper.quizId, i+1);
            theQuizPtr->AddQuestionPtr(questionPtr);

            /* Add Concept pointers */
            for(int j=0; j<questionPtr->GetConceptAmount() ;++j)
            {
                Concept* conceptPtr = questionPtr->GetConceptPtr(j);
                if(!theQuizPtr->ConceptExist(conceptPtr))
                    theQuizPtr->AddConceptPtr(conceptPtr);
            }
        }
        theQuizPtr->UpdateConceptAmount();  // Update concept amount

        // Add Answer Sheet pointers to Quiz
        for(int i=0; i<helper.studentAmount; ++i)
            theQuizPtr->AddAnswerSheetPtr(GetAnswerSheetPtr(helper.courseId, helper.quizId, helper.studentIds[i]));

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
        for(int i=0; i<helper.studentAmount; ++i)
        {
            Student* aStudentPtr = GetStudentPtr(helper.studentIds[i]);
            int studentId = aStudentPtr->GetStudentId();
            AnswerSheet* aAnswerSheetPtr = GetAnswerSheetPtr(helper.courseId, helper.quizId, studentId);
            aStudentPtr->AddAnswerSheetPtr(aAnswerSheetPtr);
        }

        // Grade one quiz after loading
        GradeOneQuiz(helper.courseId, helper.quizId);
    }
    else
    {
        cout << "Can't add the quiz. The Quiz " + quizPtr->GetCourseId() + "-" + quizPtr->GetQuizId() + " exists" << endl;
    }
}

void GradeAnalysis::GradeOneQuiz(string courseId, string quizId){
    Quiz* quizPtr = GetQuizPtr(courseId, quizId);

    // Grade Answer Sheets
    for(int i=0; i<quizPtr->GetStudentAmount(); ++i)
    {
        AnswerSheet* asPtr = quizPtr->GetAnswerSheetPtr(i);
        int error=0;

        for(int j=0; j<quizPtr->GetQuestionAmount(); ++j)
        {
            string key = asPtr->GetQuestionPtr(j)->GetAnswerKey();
            string studentAnswer = asPtr->GetAnswer(j);
            if(studentAnswer == key)
                asPtr->AddGradedAnswer(true);
            else
            {
                asPtr->AddGradedAnswer(false);
                error++;
            }
        }

        // Update the error number
        asPtr->SetErrorNum(error);

        // Set error rate
        asPtr->SetErrorRate(error/(double)asPtr->GetQuestionAmount());
    }
}

void GradeAnalysis::AnalyzeOneQuiz(string courseId, string quizId){

    Quiz* quizPtr = GetQuizPtr(courseId, quizId);

    // Introduction of the quiz
    string title = quizPtr->GetCourseId() + "-" + quizPtr->GetQuizId() + " Analysis Report";
    string statTitle = myTools.RepeatString("-",12) + " Basic Statistics " + myTools.RepeatString("-",12);

    int qNum = quizPtr->GetQuestionAmount();
    int sNum = quizPtr->GetStudentAmount();
    int cNum = quizPtr->GetConceptAmount();

    // Get Basic Statistics
    vector<double> errorRates;
    for(int i=0; i<sNum; ++i)
        errorRates.push_back(quizPtr->GetAnswerSheetPtr(i)->GetErrorRate());
    double errorRateMean = myTools.GetMean(errorRates);
    double errorRateSD = myTools.GetSD(errorRates);

    // Print Basic Information
    cout << "\n" << myTools.RepeatString("=",title.length()+18) << "\n"
        << myTools.RepeatString(" ",9) << title << myTools.RepeatString(" ",9)
        << "\n" << myTools.RepeatString("=",title.length()+18) << "\n" << endl;

    cout << statTitle << "\n"
        << qNum << " Questions, " << sNum << " Students, " << cNum << " Concepts" << "\n"
        << myTools.SpaceString("Avg ErrorRate", 17) << "--->  " << myTools.Round(errorRateMean,3) * 100 << "%" << "\n"
        << myTools.SpaceString("SD of ErrorRate",17) << "--->  " << myTools.Round(errorRateSD,3) * 100 << "%" << "\n" << endl;

    // By Concept Analysis
    string conceptTitle = myTools.RepeatString("-",12) + " Tested Concepts " + myTools.RepeatString("-",12);
    string textbook = quizPtr->GetConceptPtr(0)->GetTextbook();

    cout << conceptTitle << "\n"
        << "Textbook: " << textbook << "\n" << endl;

    for(int i=0; i<quizPtr->GetConceptAmount(); ++i){
        Concept* conceptPtr = quizPtr->GetConceptPtr(i);
        string conceptId = conceptPtr->GetConceptId();
        string concept = conceptPtr->GetConcept();

        /* Get the ID of all questions which tested this concept */
        vector<Question*> questionPtrList;
        vector<string> questionIds;
        for(int j=0; j<quizPtr->GetQuestionAmount(); ++j) {
            Question* questionPtr = quizPtr->GetQuestionPtr(j);
            if(questionPtr->ConceptExist(conceptPtr)){
                questionPtrList.push_back(questionPtr);
                questionIds.push_back(to_string(questionPtr->GetQuestionId()));
            }
        }
        string questionIdString = myTools.CombineStrings(questionIds,0,questionIds.size()-1,",");

        /* Get the ID of all students who did wrong on this concept */
        vector<string> studentIds;
        for(int j=0; j<quizPtr->GetStudentAmount(); ++j){
            AnswerSheet* asPtr = quizPtr->GetAnswerSheetPtr(j);
            for(int z=0; z<questionIds.size(); ++z){
                int questionId = stoi(questionIds[z]);
                bool gradedAnswer = asPtr->GetGradedAnswer(questionId-1);

                if(!gradedAnswer)
                {
                    studentIds.push_back(to_string(asPtr->GetStudentId()));
                    break;
                }
            }
        }
        string studentIdString = myTools.CombineStrings(studentIds,0,studentIds.size()-1,",");

        cout << myTools.SpaceString(conceptId,5) << concept << "\n"
            << myTools.SpaceString("Related Questions",25) << "--->   "
            << "(" << questionIds.size() << ") " << questionIdString << "\n"
            << myTools.SpaceString("Students Made Mistake",25) << "--->   "
            << "(" << studentIds.size() << ") " << studentIdString << "\n" << endl;



    }


//    // By Student Analysis
//    for(int i=0; i<sNum ; ++i){
//        AnswerSheet* asPtr = quizPtr->GetAnswerSheetPtr(i);
//
//        int studentId = asPtr->GetStudentId();
//
//    }
}


