#include <iostream>
#include "../code/SimpleClassifier.h"

using namespace std;

int main()
{
    SimpleClassifier bc;
    MyGlobalVars vars;
    bc.fit(vars.features_file, vars.labels_file);
    bc.shape();
    bc.analyze("This is great good");
    return 0;
}