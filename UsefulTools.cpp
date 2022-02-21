//
// Created by Xinpeng Liu on 2/14/22.
//

#include "UsefulTools.h"

bool UsefulTools::FoundString(string targetStr, string textToFind) {
    bool found = false;
    if ((targetStr.find(textToFind, 0)) != string::npos) {
        found = true;
    }
    return found;
}

vector<string> UsefulTools::SplitString(string strToSplit, string splitAt) {
    vector<string> strPartList;
    int found;  // index where the splitPoint reside
    while ((found = strToSplit.find(splitAt)) != string::npos) {
        string strPart = strToSplit.substr(0, found);
        strToSplit = strToSplit.substr(found + 1);  // renew the string line
        strPartList.push_back(strPart);  // Put partial string into vector
    }
    strPartList.push_back(strToSplit);  // put last partial string into the vector
    return strPartList;
}

string UsefulTools::CombineStrings(vector<string>& listOfString, int begin,
                                   int end, string connectWith) {
    string out = "";
    for (int i = begin; i <= end; ++i) {
        out += listOfString[i];
        if(i!=end)
            out += connectWith;
    }
    return out;
}

string UsefulTools::RepeatString(string str, int times) {
    string out = "";
    for (int i = 0; i < times; ++i) out += str;
    return out;
}

int UsefulTools::RandomInt(int begin, int end) {
    /* Get random integer between begin & end */
    int diff = end - begin;
    int addOn = (rand() % (diff + 1));
    int out = begin + addOn;
    return out;
}

string UsefulTools::RandomName() {
    /* 10 most common last names in the US */
    vector<string> lastNameList = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Rodriguez", "Martinez"};

    /* 10 most common first names in the US */
    vector<string> firstNameList = {"Noah", "Oliver", "William", "James", "Alexander", "Olivia", "Ava", "Charlotte", "Sophia", "Mia"};

    /* Randomly get last name and first name */
    string randLastName = lastNameList[RandomInt(0, lastNameList.size() - 1)];
    string randFirstName = firstNameList[RandomInt(0, firstNameList.size() - 1)];
    string name = randFirstName + " " + randLastName;

    return name;
}

size_t UsefulTools::Hash(string s) {
    size_t hash = std::hash<string>{}(s);
    return hash;
}

string UsefulTools::SpaceString(string text, int space){
    if(text.length() >= space)
        return text;
    else
    {
        int extra = space - text.length();
        return (text + RepeatString(" ", extra));
    }
}
