#include <iostream>
#include "../code/CountVectorizer.h"

using namespace std;

int main(){
    CountVectorizer myCV(false, true);
    string features = "/home/jovyan/1_2270/Final_Project/CountVectorizer/data/features.txt";
    string labels = "/home/jovyan/1_2270/Final_Project/CountVectorizer/data/labels.txt";
    myCV.fit(features, labels);
    return 0;
}



    // CountVectorizer myCV(false);
    // myCV.addSentence("bad awful terrible", 0);
    // myCV.addSentence("great happy wonderful", 1);
    // myCV.addSentence("horrible ugly negative", 0);
    // myCV.addSentence("fantastic joyous bliss", 1);
    // myCV.analyze("happy negative");
    // return 0;