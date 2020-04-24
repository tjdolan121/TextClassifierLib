#ifndef SIMPLECLASSIFIER_H__
#define SIMPLECLASSIFIER_H__

#include "BaseClassifier.h"

class SimpleClassifier : public BaseClassifier
{
public:
    // Instantiates a Classifier with a CV containing the following settings:
    // binary = true
    // caseSensitive = false
    // includeStopWords = false
    SimpleClassifier();
    ~SimpleClassifier();

    // Analyze will analyze the sentiment of a sentence given by the user.
    // It should be called on a well-populated CV for best results.  It will
    // print the sentiment and return an integer representing the sentiment
    // (used for testing/extensability):
    int analyze(string sentence);

    // GetWeight takes a sentence and compares it to the sentences in
    // the CV object. It does this by averaging out the sentiment weight
    // of each individual word in the sentence. The sentiment weight of a word is
    // calculated as how many times the word is present in positive sentences
    // divided by how many times the word is present in all sentences.
    // Weight should be a float between 0 and 1, with values less than
    // .5 being "negative sentiment", values greater than .5 being "positive sentiment",
    // values equal to .5 being "neutral sentiment" and values of -1 indicating that
    // no words from the inputted sentence were present in the CV object:
    float getWeight(vector<string> sentence);
};

#endif // SIMPLECLASSIFIER_H__