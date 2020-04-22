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
   string features_file;
   string labels_file;
   bool local;

   MyGlobalVars()
   {

      local = true;
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
          "(", "..."};

      sent1 = {"This", "is", "my", "new", "sentence"};
      sent2 = {"this", "cat", "!"};

      if (local)
      {
         features_file = "/Users/thomasdolan/Desktop/1_Code/cpp_/DataStructuresCountVec/data/features.txt";
         labels_file = "/Users/thomasdolan/Desktop/1_Code/cpp_/DataStructuresCountVec/data/labels.txt";
      }
      else
      {
         features_file = "/home/jovyan/1_2270/Final_Project/CountVectorizer/data/features.txt";
         labels_file = "/home/jovyan/1_2270/Final_Project/CountVectorizer/data/labels.txt";
      }
   }
};
