#ifndef EMPTY_H__
#define EMPTY_H__

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <set>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "GlobalData.h"

using namespace std;

struct Sentence
{
  vector<int> sentence_array;
  bool label;
};

class CountVectorizer
{
public:
  // ======================CONSTRUCTORS==============================|

  // Default constructor has two options, one which takes no params,
  // which defaults to case_sensitive=true and include_stopwords=true:
  CountVectorizer();

  // And another which allows the user to choose their options:
  CountVectorizer(bool binary_, bool case_sensitive_, bool include_stopwords_);

  // Destructor:
  ~CountVectorizer();

  // ======================USER INTERFACE FUNCTIONS==================|

  // Fit will add additional (labeled) data to a CV object.  User must
  // provide an absolute filepath to the features and an absolute file-
  // path to the labels:
  void fit(string abs_filepath_to_features, string abs_filepath_to_labels);

  // Prints the dimensions of the CV object:
  void shape();

  // Prints a dictionary-like representation of the CV object (first 10):
  void head();

  // ======================HELPERS===================================|

  // Checks if a word is in the sentence.  Returns an integer casted bool:
  int is_wordInSentence(Sentence sentence_, unsigned int idx);

  // Given a sentence, pushSentenceToWordArray will update the CV's word_array
  // to incorporate newly discovered words:
  void pushSentenceToWordArray(vector<string> new_sentence_vector);

  // Given a sentence, return a fully constructed sentence object:
  shared_ptr<Sentence> createSentenceObject(vector<string> new_sentence_vector, bool label_);

  // Given a sentence, add the sentence to the CountVectorizer.  Combines
  // buildSentenceVector, pushSentenceToWordArray, and createSentenceObject
  // to accomplish this task:
  void addSentence(string new_sentence, bool label_);

  // Checks if the CV object already contains the word.
  bool CountVectorizerContainsWord(string word_to_check);

  // Given a sentence, split the sentence into a vector of words.
  // Punctuation should be its own element.
  vector<string> buildSentenceVector(string sentence_);

  // Private attribute getter functions:
  string getWord(int idx) { return word_array[idx]; }
  shared_ptr<Sentence> getSentence(int idx) { return sentences[idx]; }
  unsigned int getWordArraySize() { return word_array.size(); }
  unsigned int getSentenceCount() { return sentences.size(); }

  // Private attribute setter functions:
  void setBinary(bool bool_) { binary = bool_; }
  void setCaseSensitive(bool bool_) { case_sensitive = bool_; }
  void setIncludeStopWords(bool bool_) { include_stopwords = bool_; } // FIX ME!!!!!!!!

  friend class BaseClassifier;
  friend class SimpleClassifier;
  friend class NaiveBayesClassifier;

private:
  vector<string> word_array;
  vector<shared_ptr<Sentence>> sentences;
  bool binary;
  bool case_sensitive;
  bool include_stopwords;
};

#endif // EMPTY_H__
