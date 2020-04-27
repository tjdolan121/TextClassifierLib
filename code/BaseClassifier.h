#ifndef BASECLASSIFIER_H__
#define BASECLASSIFIER_H__

#include <iostream>
#include "CountVectorizer.h"

using namespace std;

class BaseClassifier
{
public:  // protected
    BaseClassifier();
    ~BaseClassifier();
    void fit(string abs_filepath_to_features, string abs_filepath_to_labels);
    void shape();
    void head();
    CountVectorizer CV;
    string true_label_meaning;
    string false_label_meaning;
};

#endif // BASECLASSIFIER_H__