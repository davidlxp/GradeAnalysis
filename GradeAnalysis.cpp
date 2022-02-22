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

    /* If read is not success, the emptyJudge = true.
     * In that case, we don't want to load anything
     */
    bool emptyJudge = (helper.courseId=="" && helper.quizId=="");

    // Load if the Helper is not empty and Quiz not exist
    if(emptyJudge){
        cout << "Can't add the quiz. The Reading Process failed..." << endl;
    }
    else if(!myTools.JudgePtrInList(quizPtrList, quizPtr)) {

        // Initialize all the objects and add to lists
        InitQuiz(helper);
        InitQuestion(helper);
        InitAnswerSheet(helper);
        InitStudent(helper);
        InitConcept(helper);

        // Add pointer links to objects (interrelationship)
        LinkQuestion(helper);
        LinkQuiz(helper);
        LinkAnswerSheet(helper);
        LinkStudent(helper);

        // Grade one quiz after loading
        GradeOneQuiz(helper.courseId, helper.quizId);

        cout << "\n" << "Success! Loading Complete." << endl;
    }
    else
    {
        cout << "Can't add the quiz. The Quiz "
        + quizPtr->GetCourseId() + "-" + quizPtr->GetQuizId() + " exists..." << endl;
    }
}

void GradeAnalysis::InitQuiz(ReadHelper& helper){
    Quiz* quizPtr = new Quiz(helper.courseId, helper.quizId);
    quizPtr->SetQuestionAmount(helper.questionAmount);                        // set question amount in Quiz
    quizPtr->SetStudentAmount(helper.studentAmount);                          // set student amount in Quiz
    AddQuizPtr(quizPtr);
}

void GradeAnalysis::InitQuestion(ReadHelper& helper){
    for (int i = 0; i < helper.questionAmount; ++i) {
        int questionId = i+1;
        Question *questionPtr = new Question(
                helper.courseId, helper.quizId, questionId, helper.answerKey[i]);
        AddQuestionPtr(questionPtr);
    }
}

void GradeAnalysis::InitAnswerSheet(ReadHelper& helper){
    for (int i = 0; i < helper.studentAmount; ++i) {
        AnswerSheet *answerSheetPtr = new AnswerSheet(                        // init one answer sheet
                helper.courseId, helper.quizId, helper.studentIds[i]);
        answerSheetPtr->SetQuestionAmount(helper.questionAmount);             // set question amount
        for (int j = 0; j < helper.questionAmount; ++j)                       // loading the student answers
            answerSheetPtr->AddAnswer(helper.studentAnswer[i][j]);
        AddAnswerSheetPtr(answerSheetPtr);                                    // add answer sheet to vector in GradeAnalysis
    }
}

void GradeAnalysis::InitStudent(ReadHelper& helper){
    for (int i = 0; i < helper.studentAmount; ++i) {
        Student *studentPtr = new Student(
                myTools.RandomName(), helper.studentIds[i]);
        AddStudentPtr(studentPtr);
    }
}

void GradeAnalysis::InitConcept(ReadHelper& helper){
    for (int i = 0; i < helper.conceptList.size(); ++i) {

        string textbook = helper.conceptList[i][0];
        int chapterId = stoi(helper.conceptList[i][1]);
        string chapter = helper.conceptList[i][2];
        string conceptId = helper.conceptList[i][3];
        string concept = helper.conceptList[i][4];
        int page = stoi(helper.conceptList[i][5]);

        Concept *conceptPtr = new Concept(textbook, conceptId);               // init concept and add everything
        conceptPtr->SetChapterId(chapterId);
        conceptPtr->SetChapter(chapter);
        conceptPtr->SetConcept(concept);
        conceptPtr->SetPage(page);

        AddConceptPtr(conceptPtr);
    }
}

void GradeAnalysis::LinkQuestion(ReadHelper& helper){

    // Add Concept pointers to Question objects
    for (int i = 0; i < helper.mapQuestionConcept.size(); ++i) {

        vector<string> aMap = helper.mapQuestionConcept[i];                   // a map shows relation between questions & concepts
        int questionId = stoi(aMap[0]);
        string concept = aMap[1];

        Question *aQuestion = GetQuestionPtr(                                 // find the pointer of specific question
                helper.courseId, helper.quizId, questionId);
        Concept *aConcept = GetConceptPtrByName(                              // find the pointer of specific concept
                helper.textbook, concept);

        aQuestion->AddConceptPtr(aConcept);                                   // link a concept to a question
        aQuestion->UpdateConceptAmount();                                     // update the tracker ("num of concepts" in this Question)
    }
}

void GradeAnalysis::LinkQuiz(ReadHelper& helper){

    string courseId = helper.courseId;
    string quizId = helper.quizId;

    // Add Question & Concept pointers to Quiz
    Quiz *theQuizPtr = GetQuizPtr(courseId, quizId);
    for(int i=0; i<helper.questionAmount; ++i)
    {
        /* Add Question pointers */
        int questionId = i+1;
        Question* questionPtr = GetQuestionPtr(
                courseId, quizId, questionId);
        theQuizPtr->AddQuestionPtr(questionPtr);

        /* Add Concept pointers */
        for(int j=0; j<questionPtr->GetConceptAmount() ;++j)
        {
            Concept* conceptPtr = questionPtr->GetConceptPtr(j);
            if(!theQuizPtr->ConceptExist(conceptPtr))                         // check if Concept is already in the list
                theQuizPtr->AddConceptPtr(conceptPtr);
        }
    }
    theQuizPtr->UpdateConceptAmount();                                        // update concept amount

    // Add AnswerSheet pointers to Quiz
    for(int i=0; i<helper.studentAmount; ++i)
        theQuizPtr->AddAnswerSheetPtr(GetAnswerSheetPtr(
                courseId, quizId, helper.studentIds[i]));
}

void GradeAnalysis::LinkAnswerSheet(ReadHelper& helper){

    string courseId = helper.courseId;
    string quizId = helper.quizId;

    // Add Question pointers to AnswerSheet objects
    for(int i=0; i<helper.studentAmount; ++i)
    {
        int studentId = helper.studentIds[i];
        AnswerSheet* aAnswerSheetPtr = GetAnswerSheetPtr(                     // get an answer sheet
                courseId, quizId, studentId);
        for(int j=0; j<helper.questionAmount; ++j)                            // add question objects for an answer sheet
        {
            int questionId = j+1;
            aAnswerSheetPtr->AddQuestionPtr(
                    GetQuestionPtr(courseId, quizId, questionId));
        }
    }
}

void GradeAnalysis::LinkStudent(ReadHelper& helper){

    string courseId = helper.courseId;
    string quizId = helper.quizId;

    // Add Answer Sheet pointers to Student
    for(int i=0; i<helper.studentAmount; ++i)
    {
        Student* aStudentPtr = GetStudentPtr(helper.studentIds[i]);           // get a student pointer
        int studentId = aStudentPtr->GetStudentId();
        AnswerSheet* aAnswerSheetPtr = GetAnswerSheetPtr(                     // get the answer sheet of this student
                courseId, quizId, studentId);
        aStudentPtr->AddAnswerSheetPtr(aAnswerSheetPtr);                      // add answer sheet pointer to the student
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

void GradeAnalysis::BasicAnalysis(string courseId, string quizId){
    Quiz* quizPtr = GetQuizPtr(courseId, quizId);

    // Introduction of the quiz
    string statTitle = "<[*]>" + myTools.RepeatString("-",12) + " Basic Statistics " + myTools.RepeatString("-",12) + "<[*]>";

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
    cout << statTitle << "\n"
         << qNum << " Questions, " << sNum << " Students, " << cNum << " Concepts" << "\n"
         << myTools.SpaceString("Avg ErrorRate", 17) << "--->  " << myTools.Round(errorRateMean,3) * 100 << "%" << "\n"
         << myTools.SpaceString("SD of ErrorRate",17) << "--->  " << myTools.Round(errorRateSD,3) * 100 << "%" << "\n" << endl;
}

void GradeAnalysis::AnalyzeConcept(string courseId, string quizId){
    Quiz* quizPtr = GetQuizPtr(courseId, quizId);

    // By Concept Analysis
    string conceptTitle = "<[*]>" + myTools.RepeatString("-",12)
            + " Tested Concepts " + myTools.RepeatString("-",12) + "<[*]>";
    string textbook = quizPtr->GetConceptPtr(0)->GetTextbook();

    cout << conceptTitle << "\n"
         << "Textbook: " << textbook << "\n\n"
         <<  myTools.SpaceString("[Students Made Mistake]",25) << " --->  "
         << "Students who did wrong on at least 1 question which tested this concept." << "\n"
         <<  myTools.SpaceString("[Students Mistake Ratio]",25) << " --->  "
         << "% of 'Students Made Mistake' out of all students." << "\n"
         << myTools.SpaceString("[Students Failed]", 25) << " --->  "
         << "Students who did wrong on ALL questions which tested this concept." << "\n"
         <<  myTools.SpaceString("[Students Failed Ratio]",25) << " --->  "
         << "% of 'Students Failed' out of all students." << "\n" << endl;

    for(int i=0; i<quizPtr->GetConceptAmount(); ++i){
        Concept* conceptPtr = quizPtr->GetConceptPtr(i);
        string conceptId = conceptPtr->GetConceptId();
        string concept = conceptPtr->GetConcept();

        /* Get the ID of all questions which tested this concept */
        vector<Question*> questionPtrList;
        vector<string> questionIds;
        for(int j=0; j<quizPtr->GetQuestionAmount(); ++j) {
            Question* questionPtr = quizPtr->GetQuestionPtr(j);                // get pointer of question which in this quiz
            if(questionPtr->ConceptExist(conceptPtr)){                         // check if a question relates to a concept
                questionPtrList.push_back(questionPtr);                        // if yes, save question pointer
                questionIds.push_back(to_string(                               // also records question ID
                        questionPtr->GetQuestionId()));
            }
        }
        string questionIdString = myTools.CombineStrings(                      // turn recorded question IDs to a string
                questionIds,0,questionIds.size()-1,",");

        /* Get the ID of all students who did wrong on this concept */
        vector<string> studentIdsMistake;                                      // students who did at least 1 question wrong
        vector<string> studentIdsFail;                                         // students did all questions wrong
        for(int j=0; j<quizPtr->GetStudentAmount(); ++j){
            AnswerSheet* asPtr = quizPtr->GetAnswerSheetPtr(j);                // get 1 student's answer sheet

            int error = 0;                                                     // for 1 answer sheet, track how many error on related questions
            for(int z=0; z<questionIds.size(); ++z){                           // check the grade of all related questions in this answer sheet
                int questionId = stoi(questionIds[z]);
                bool gradedAnswer = asPtr->                                    // get graded answer using question ID
                        GetGradedAnswer(questionId-1);

                if(!gradedAnswer)                                              // track how many error on related questions
                    error++;
            }
            if(error != 0)                                                     // add students who did at least 1 wrong on questions
                studentIdsMistake.push_back(
                        to_string(asPtr->GetStudentId()));

            if(error == questionIds.size())                                    // add students who did all wrong on questions
                studentIdsFail.push_back(
                        to_string(asPtr->GetStudentId()));
        }
        string stuMistakeString = myTools.CombineStrings(                      // a string of student who made mistake
                studentIdsMistake,0,studentIdsMistake.size()-1,",");
        string stuFailString = myTools.CombineStrings(                         // a string of student who failed
                studentIdsFail,0,studentIdsFail.size()-1,",");

        /* Calculate Ratio */
        double studentMistakeRatio =                                           // calculate % of student made mistake
                studentIdsMistake.size() / (double)quizPtr->GetStudentAmount();
        double studentFailRatio =                                              // calculate % of student failed this concept
                studentIdsFail.size() / (double)quizPtr->GetStudentAmount();

        /* Print Concept Analysis */
        cout << myTools.SpaceString(conceptId,5) << concept << "\n"
             << myTools.SpaceString("Related Questions",25) << "--->   "
             << "(" << questionIds.size() << ") " << questionIdString << "\n"

             << myTools.SpaceString("Students Made Mistake",25) << "--->   "
             << "(" << studentIdsMistake.size() << ") " << stuMistakeString << "\n"
             << myTools.SpaceString("Student Mistake Ratio",25) << "--->   "
             << myTools.Round(studentMistakeRatio,3) * 100 << "%" << "\n"

             << myTools.SpaceString("Students Failed",25) << "--->   "
             << "(" << studentIdsFail.size() << ") " << stuFailString << "\n"
             << myTools.SpaceString("Student Failed Ratio",25) << "--->   "
             << myTools.Round(studentFailRatio,3) * 100 << "%" << "\n" << endl;
    }
}

void GradeAnalysis::AnalyzeStudent(string courseId, string quizId) {
    Quiz* quizPtr = GetQuizPtr(courseId, quizId);

    // By Student Analysis
    string studentTitle = "<[*]>" + myTools.RepeatString("-",12)
                          + " By Student Analysis " + myTools.RepeatString("-",12) + "<[*]>";

    cout << studentTitle << "\n\n"
        << myTools.SpaceString("[Student Answers]",25) << " --->  "
        << "The student's response to the questions in the quiz." << "\n"
        << myTools.SpaceString("[Answer Keys]",25) << " --->  "
        << "The answer keys of the quiz." << "\n"
         << myTools.SpaceString("[Questions Did Wrong]",25) << " --->  "
         << "The ID of questions which the student did wrong." << "\n"
         << myTools.SpaceString("[Error Rate]",25) << " --->  "
         << "% of error out of all questions." << "\n"
         << myTools.SpaceString("[Concepts Made Mistake]",25) << " --->  "
         << "Concepts from the questions which the student did wrong." << "\n" << endl;


    for(int i=0; i<quizPtr->GetStudentAmount(); ++i) {
        AnswerSheet *asPtr = quizPtr->GetAnswerSheetPtr(i);                    // get pointer of one answer sheet
        double errorRate = asPtr->GetErrorRate();

        /* Get student ID and name */
        int studentId = asPtr->GetStudentId();
        string student = GetStudentPtr(studentId)->GetStudent();

        /* Get ID of questions the student did wrong */
        vector<string> errorQueIds;                                            // a list to record the ID of error questions
        for (int j = 0; j < asPtr->GetQuestionAmount(); ++j) {
            bool grade = asPtr->GetGradedAnswer(j);                            // get grade of a question
            if (!grade)                                                        // if the grade is false, add this question to list
                errorQueIds.push_back(to_string(j + 1));
        }
        string errorQueString = myTools.CombineStrings(                        // a string of IDs of error questions
                errorQueIds, 0, errorQueIds.size() - 1, ",");

        /* Get concepts the student did wrong */
        vector<string> errorConcepts;                                          // list for storing mistake concepts
        for (int j = 0; j < asPtr->GetQuestionAmount(); ++j) {
            bool grade = asPtr->GetGradedAnswer(j);                            // get grade of one question

            if (!grade)                                                         // if did wrong on this question, find its concepts
            {
                Question *questionPtr = asPtr->GetQuestionPtr(j);
                for (int z = 0;
                     z < questionPtr->GetConceptAmount(); ++z) {                // find all concepts of the question and add to list
                    string conceptId = questionPtr->
                            GetConceptPtr(z)->GetConceptId();
                    string concept = questionPtr->
                            GetConceptPtr(z)->GetConcept();
                    string aConcept = myTools.SpaceString(conceptId, 5) + concept;

                    bool exist = myTools.ItemExist(errorConcepts, aConcept);
                    if (!exist)                                                 // don't add to list if the concept is already added
                        errorConcepts.push_back(aConcept);
                }
            }
        }

        /* Get student-answers and answer-keys */
        vector<string> studentAnswers;
        for(int j=0; j<asPtr->GetQuestionAmount(); ++j)
            studentAnswers.push_back(asPtr->GetAnswer(j));
        string stuAnswersString =  myTools.CombineStrings(                      // a string of student answers
                studentAnswers,0,studentAnswers.size()-1,",");

        vector<string> answerKeys;
        for(int j=0; j<asPtr->GetQuestionAmount(); ++j)
            answerKeys.push_back(
                    asPtr->GetQuestionPtr(j)->GetAnswerKey());
        string answerKeysString = myTools.CombineStrings(                      // a string of answer keys
                answerKeys,0,answerKeys.size()-1,",");

        /* Print result of "By Student Analysis" */
        cout << ">>> " << student << " (" << studentId << ")" << " <<<" << "\n"
             << myTools.SpaceString("Student Answers", 22) << "--->  "
             << stuAnswersString << "\n"
             << myTools.SpaceString("Answer Keys", 22) << "--->  "
             << answerKeysString << "\n"
             << myTools.SpaceString("Questions Did Wrong", 22) << "--->  "
             << "(" << errorQueIds.size() << ") " << errorQueString << "\n"
             << myTools.SpaceString("Error Rate", 22) << "--->  "
             << myTools.Round(errorRate, 3) * 100 << "%" << "\n"
             << myTools.SpaceString("Concepts Made Mistake", 22) << "--->  "
             << "(" << errorConcepts.size() << ") " << "\n";

        for (int j = 0; j < errorConcepts.size(); ++j)
            cout << myTools.RepeatString(" ", 1) << errorConcepts[j] << "\n";
        cout << endl;
    }
}

void GradeAnalysis::AnalyzeQuestion(string courseId, string quizId) {
    Quiz* quizPtr = GetQuizPtr(courseId, quizId);

    // By Question Analysis
    string questionTitle = "<[*]>" + myTools.RepeatString("-",12) +
            " By Question Analysis " + myTools.RepeatString("-",12) + "<[*]>";

    cout << questionTitle << "\n\n"
        << myTools.SpaceString("[Answer Key]",25) << " --->  "
        << "The student's response to the questions in the quiz." << "\n"
        << myTools.SpaceString("[Students Did it Wrong]",25) << " --->  "
        << "ID of students who did wrong on this question." << "\n"
        << myTools.SpaceString("[Top Error Answer]",25) << " --->  "
        << "The most frequent error answer from students who did this question wrong" << "\n"
        << myTools.SpaceString("[Related Concept]",25) << " --->  "
        << "The concepts which tested in this question." << "\n" << endl;

    for(int i=0; i<quizPtr->GetQuestionAmount(); ++i) {
        string questionId = to_string(i + 1);
        Question *questionPtr = quizPtr->GetQuestionPtr(i);
        string answerKey = questionPtr->GetAnswerKey();                          // answer key of this question

        /* Get all concepts which are tested in this question */
        vector<string> testedConcepts;
        for (int j = 0; j < questionPtr->GetConceptAmount(); ++j) {
            Concept *conceptPtr = questionPtr->GetConceptPtr(j);
            string conceptId = conceptPtr->GetConceptId();
            string concept = conceptPtr->GetConcept();
            string aConcept = myTools.SpaceString(conceptId, 5) + concept;

            testedConcepts.push_back(aConcept);
        }

        /* Get ID of all students which did this question wrong
         * Also track all the error answers and their frequency
         * */
        vector<string> studentIdsMistake;                                        // list tracks ID of students who makes mistake on this question
        map<string, int> mistakeMap;                                             // a map tracks the mistake answers and their frequency
        for (int j = 0; j < quizPtr->GetStudentAmount(); ++j) {
            AnswerSheet *asPtr = quizPtr->GetAnswerSheetPtr(j);
            string answer = asPtr->GetAnswer(i);
            bool grade = asPtr->GetGradedAnswer(i);
            if (!grade) {
                studentIdsMistake.push_back(                                     // add a student ID to the list
                        to_string(asPtr->GetStudentId()));

                if(mistakeMap.empty() || mistakeMap.count(answer)==0)            // insert error-answer and frequency into the map
                    mistakeMap[answer] = 1;
                else{
                    mistakeMap[answer]++;
                }
            }
        }
        string stuMistakeString = myTools.CombineStrings(                        // a string of student who made mistake on this question
                studentIdsMistake, 0, studentIdsMistake.size() - 1, ",");

        /* Find the error answer with the top frequency */
        string topErrorString;
        string topErrorAnswer;
        int topFreq = 0;

        if(!mistakeMap.empty()) {
            topErrorAnswer = mistakeMap.begin()->first;                          // the key of the first pair in the map
            topFreq = mistakeMap.begin()->second;                                // the value of the first pair in the map
            for (auto x = mistakeMap.begin(); x != mistakeMap.end(); ++x) {
                if (x->second > topFreq) {
                    topFreq = x->second;
                    topErrorAnswer = x->first;
                }
            }
            topErrorString = topErrorAnswer + " ---> "                         // a string of top error answer and its frequency
                    + to_string(topFreq) + " time";
        }
        else {
            topErrorString = "None";
        }

        /* Print result of "By Question Analysis" */
        cout << "Question " << questionId << "\n"
            << myTools.SpaceString("Answer Key", 23) << "--->  "
            << answerKey << "\n"
            << myTools.SpaceString("Students Did it Wrong", 23) << "--->  "
            << "(" << studentIdsMistake.size() << ") " << stuMistakeString << "\n"
            << myTools.SpaceString("Top Error Answer", 23) << "--->  "
            << topErrorString << "\n"
            << myTools.SpaceString("Related Concepts", 23) << "--->  "
            << "(" << testedConcepts.size() << ") " << "\n";

        for (int j = 0; j < testedConcepts.size(); ++j)
            cout << myTools.RepeatString(" ", 1) << testedConcepts[j] << "\n";
        cout << endl;
    }
}

void GradeAnalysis::AnalyzeOneQuiz(string courseId, string quizId){

    /* Header */
    Quiz* quizPtr = GetQuizPtr(courseId, quizId);
    string title = quizPtr->GetCourseId() + "-" + quizPtr->GetQuizId() + " Analysis Report";

    cout << "\n" << myTools.RepeatString("=",title.length()+18) << "\n"
         << myTools.RepeatString(" ",9) << title << myTools.RepeatString(" ",9)
         << "\n" << myTools.RepeatString("=",title.length()+18) << "\n" << endl;

    /* All Analysis */
    BasicAnalysis(courseId, quizId);
    AnalyzeConcept(courseId, quizId);
    AnalyzeStudent(courseId, quizId);
    AnalyzeQuestion(courseId, quizId);

    /* Ending */
    string ending = "END OF THE ANALYSIS";
    cout << "\n" << myTools.RepeatString("=",ending.length()+18) << "\n"
        << myTools.RepeatString(" ",9) << ending << myTools.RepeatString(" ",9)
        << "\n" << myTools.RepeatString("=",ending.length()+18) << "\n\n"
        << "© 2022 BMCC-Xinpeng Liu. All Rights Reserved." << "\n\n" << endl;
}


