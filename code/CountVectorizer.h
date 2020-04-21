#ifndef EMPTY_H__
#define EMPTY_H__

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <set>
#include <algorithm>
#include <fstream>
#include "GlobalData.h"

using namespace std;

struct Sentence {
  vector<int> sentence_array;
  bool label;
};

class CountVectorizer {
public:
  // Constructor/Destructor
  CountVectorizer(bool case_sensitive_);
  ~CountVectorizer();

  // ===============PRIMARY FUNCTIONS =============== |

  int analyze(string sentence);

  void train();

  float getWeight(vector<string> sentence_);

  int is_wordInSentence(Sentence sentence_, unsigned int idx);

  // Given a sentence, pushSentenceToWordArray will update the CV's word_array 
  // to incorporate newly discovered words.
  void pushSentenceToWordArray(vector<string> new_sentence_vector);

  // Given a sentence, return a sentence object.
  shared_ptr<Sentence> createSentenceObject(vector<string> new_sentence_vector, bool label_);

  // Given a sentence, add the sentence to the CountVectorizer.
  void addSentence(string new_sentence, bool label_);

// ======================UTILITIES========================= |

  string getWord(int idx) {return word_array[idx];}
  shared_ptr<Sentence> getSentence(int idx) {return sentences[idx];}
  unsigned int getSize() {return word_array.size();}  // TODO: make function name more explicit
  bool CountVectorizerContainsWord(string word_to_check);

  // Given a sentence, split the sentence into a vector of words.  
  // Punctuation should be its own element.
  vector<string> buildSentenceVector(string sentence_);  
    
private:
  vector<string> word_array;
  vector< shared_ptr<Sentence> > sentences;
  bool case_sensitive;
};



#endif // EMPTY_H__



