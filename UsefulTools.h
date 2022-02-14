//
// Created by Xinpeng Liu on 2/14/22.
//

#ifndef GRADEANALYSIS_USEFULTOOLS_H
#define GRADEANALYSIS_USEFULTOOLS_H


#include <iostream>
#include <string>
#include <vector>
using namespace std;

// "UsefulTools" Class for storing useful function in this project
class UsefulTools {
public:
    /**
     * @Brief check if a string is within another string
     */
    bool FoundString(string, string);

    /**
     * @Brief split a string into a list of string partials
     */
    vector<string> SplitString(string, string);

    /**
     * @Brief combine a list of string partials to one string
     */
    string CombineStrings(vector<string>&, int, int, string);

    /**
     * @Brief repeat a string N times (eg. =========)
     */
    string RepeatString(string, int);

    /**
     * @Brief generating an randomly integer between a and b, include themselves
     */
    int RandomInt(int, int);

    /**
     * @Brief generating an randomly name
     */
    string RandomName();

    /**
     * @Brief template function judges whether an object ptr exist in a list of
     * object ptr
     */
    template <class T>
    bool JudgePtrInList(vector<T*>&, T*);

    /**
     * @Brief template function adds an object ptr into an existing a list of
     * object ptr
     */
//    template <class T>
//    bool AddPtrToList(vector<T*>&, T*);

    /**
     * @Brief hashing a string to a unique sequence of int
     */
    size_t Hash(string);
};

template <class T>
bool UsefulTools::JudgePtrInList(vector<T*>& onePtrList, T* objPtr) {
    bool judge = false;
    int size = onePtrList.size();
    for (int i = 0; i < size; ++i) {
        if (onePtrList[i]->GetId() == objPtr->GetId()) {
            judge = true;
            break;
        }
    }
    return judge;
}

//template <class T>
//bool UsefulTools::AddPtrToList(vector<T*>& onePtrList, T* objPtr) {
//    bool judge = JudgePtrInList(onePtrList, objPtr);
//    if (!judge)
//        onePtrList.push_back(objPtr);
//    else
//        cout << "The object is already exist" << endl;
//}

#endif //GRADEANALYSIS_USEFULTOOLS_H
