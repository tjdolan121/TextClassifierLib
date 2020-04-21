#include <iostream>
#include "../code/CountVectorizer.h"

using namespace std;

int main(){
    CountVectorizer myCV(false);
    myCV.train();
    return 0;
}



    // CountVectorizer myCV(false);
    // myCV.addSentence("bad awful terrible", 0);
    // myCV.addSentence("great happy wonderful", 1);
    // myCV.addSentence("horrible ugly negative", 0);
    // myCV.addSentence("fantastic joyous bliss", 1);
    // myCV.analyze("happy negative");
    // return 0;