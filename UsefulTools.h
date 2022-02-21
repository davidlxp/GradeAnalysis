//
// Created by Xinpeng Liu on 2/14/22.
//

#ifndef GRADEANALYSIS_USEFULTOOLS_H
#define GRADEANALYSIS_USEFULTOOLS_H


#include <iostream>
#include <string>
#include <vector>
#include<cmath>
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
    template <class T>
    void AddPtrToList(vector<T*>&, T*);

    /**
     * @Brief template function gets an object ptr from a list
     */
    template <class T>
    T* GetPtrById(vector<T*>&, size_t);

    /**
     * @Brief hashing a string to a unique sequence of int
     */
    size_t Hash(string);

    /**
     * @Brief reformat the string to make it occupy a standard space
     */
    string SpaceString(string, int);

    /**
     * @Brief get mean value from a vector of number
     */
    template <class T>
    T GetMean(vector<T>&);

    /**
     * @Brief get standard deviation value from a vector of number
     */
    template <class T>
    T GetSD(vector<T>&);

    /**
     * @Brief round a number
     */
    template <class T>
    T Round(T, int);

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

template <class T>
void UsefulTools::AddPtrToList(vector<T*>& onePtrList, T* objPtr) {
    bool judge = JudgePtrInList(onePtrList, objPtr);
    if (!judge)
        onePtrList.push_back(objPtr);
    else
        cout << "The object of type [" << typeid(*objPtr).name() << "] is already exist" << endl;
}

template <class T>
T* UsefulTools::GetPtrById(vector<T*>& onePtrList, size_t uniqueId) {
    T *objPtr = nullptr;
    for (int i = 0; i < onePtrList.size(); ++i) {
        if (onePtrList[i]->GetId() == uniqueId) {
            objPtr = onePtrList[i];
            break;
        }
    }
    return objPtr;
}

template <class T>
T UsefulTools::GetMean(vector<T>& list){
    T sum=0;
    for(int i=0; i<list.size(); ++i){
        sum += list[i];
    }
    return (sum / list.size());
}

template <class T>
T UsefulTools::GetSD(vector<T>& list){
    T mean = GetMean(list);
    T agg = 0;
    for(int i=0; i<list.size(); ++i)
        agg += pow(list[i] - mean, 2);
    return (sqrt(agg / list.size()));
}

template <class T>
T UsefulTools::Round(T num, int numDecimal){
    int multi = pow(10, numDecimal);
    return(round(num * multi) / multi);
}

#endif //GRADEANALYSIS_USEFULTOOLS_H
