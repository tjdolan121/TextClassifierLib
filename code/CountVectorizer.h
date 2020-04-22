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
  CountVectorizer(bool case_sensitive_, bool include_stopwords_);

  // Destructor:
  ~CountVectorizer();

  // ======================USER INTERFACE FUNCTIONS==================|

  // Analyze will analyze the sentiment of a sentence given by the user.
  // It should be called on a well-populated CV for best results.  It will
  // print the sentiment and return an integer representing the sentiment
  // (used for testing/extensability):
  int analyze(string sentence);

  // Fit will add additional (labeled) data to a CV object.  User must
  // provide an absolute filepath to the features and an absolute file-
  // path to the labels:
  void fit(string abs_filepath_to_features, string abs_filepath_to_labels);

  // Prints the dimensions of the CV object:
  void shape();

  // Prints a dictionary-like representation of the CV object (first 10):
  void head();

  // ======================HELPERS===================================|

  // GetWeight takes a sentence and compares it to the sentences in
  // the CV object. It does this by averaging out the sentiment weight
  // of each individual word in the sentence. The sentiment weight of a word is
  // calculated as how many times the word is present in positive sentences
  // divided by how many times the word is present in all sentences.
  // Weight should be a float between 0 and 1, with values less than
  // .5 being "negative sentiment", values greater than .5 being "positive sentiment",
  // values equal to .5 being "neutral sentiment" and values of -1 indicating that
  // no words from the inputted sentence were present in the CV object:
  float getWeight(vector<string> sentence_);

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

private:
  vector<string> word_array;
  vector<shared_ptr<Sentence>> sentences;
  bool case_sensitive;
  bool include_stopwords;
};

#endif // EMPTY_H__
