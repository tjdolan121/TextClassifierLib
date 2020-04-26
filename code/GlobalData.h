#include <string>
#include <vector>

using namespace std;

class MyGlobalVars
{
public:
   int POS;
   int NEG;
   int NEU;
   int UNK;
   set<char> punctuation;
   set<string> stopWords;
   vector<string> sent1;
   vector<string> sent2;
   vector<string> sent3;
   string features_file;
   string labels_file;

   MyGlobalVars()
   {
      POS = 1;
      NEG = 0;
      NEU = -2;
      UNK = 0;

      punctuation = {
          '!', '?', '/'};

      stopWords = {
          "The", "the", "a", "A", "an", "An",
          "This", "this", "That", "that", "is",
          "Is", "my", "My", ".", ":", ",", ";", "\'", ")"
                                                      "(",
          "..."};

      sent1 = {"This", "is", "my", "new", "sentence"};
      sent2 = {"this", "cat", "!"};
      sent3 = {"cake", "apple", "cake", "cake", "banana", "apple"};
      features_file = "../data/features.txt";
      labels_file = "../data/labels.txt";
   }
};
