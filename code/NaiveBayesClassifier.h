#ifndef NAIVEBAYESCLASSIFIER_H__
#define NAIVEBAYESCLASSIFIER_H__

#include <cmath>
#include "BaseClassifier.h"

class NaiveBayesClassifier : public BaseClassifier
{
public:
    NaiveBayesClassifier();
    ~NaiveBayesClassifier();
    int analyze(string sentence);

    int totalWords();
    int totalWordsOfType(bool label_);
    float pOfType(bool label_);
    int countOccurances(string word);
    int countOccurancesOfType(string word, bool label_);
    float getWeight(vector<string> sentence, bool label_);

private:
    float smoothing_param_m = 1.0;
    float smoothing_param_p = 0.5;
};

#endif // NAIVEBAYESCLASSIFIER_H__