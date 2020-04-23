#include <iostream>
#include "../code/CountVectorizer.h"

using namespace std;

int main()
{
    CountVectorizer myCV(true, false, true);
    MyGlobalVars vars;
    myCV.fit(vars.features_file, vars.labels_file);
    myCV.shape();
    myCV.head();
    myCV.analyze("I loved this place!");
    return 0;
}