// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/CountVectorizer.h"

#include <iostream>
#include <string>

using namespace std;


class test_CountVectorizer : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
	}
    
	// this function runs before every TEST_F function
	void SetUp() override {
    }

	// this function runs after every TEST_F function
	void TearDown() override {
	}
};


TEST_F(test_CountVectorizer, pushSentenceToWordArray){

    CountVectorizer caseSensitiveCV(true);
	caseSensitiveCV.pushSentenceToWordArray(sent1);
    // | This | is | my | new | sentence |

    ASSERT_EQ(caseSensitiveCV.getWord(0), "This");
	ASSERT_EQ(caseSensitiveCV.getWord(3), "new");
	ASSERT_EQ(caseSensitiveCV.getSize(), 5);

	caseSensitiveCV.pushSentenceToWordArray(sent2);
	// | This | is | my | new | sentence | this | cat |

	ASSERT_EQ(caseSensitiveCV.getWord(5), "this");
	ASSERT_EQ(caseSensitiveCV.getWord(6), "cat");
	ASSERT_EQ(caseSensitiveCV.getWord(7), "!");
	ASSERT_EQ(caseSensitiveCV.getSize(), 8);

}

TEST_F(test_CountVectorizer, createSentenceObject){

    CountVectorizer caseSensitiveCV(true);
	caseSensitiveCV.pushSentenceToWordArray(sent1);
    // | This | is | my | new | sentence |

	shared_ptr<Sentence> newSent1;
	newSent1 = caseSensitiveCV.createSentenceObject({"my", "sentence"}, false);
	// sentence array = | 0 | 0 | 1 | 0 | 1 |   label = false

	shared_ptr<Sentence> newSent2;
	newSent2 = caseSensitiveCV.createSentenceObject({"This", "is", "my", "sentence"}, true);
	// sentence array = | 1 | 1 | 1 | 0 | 1 |   label = true

	vector<int> sent1Expected = {0, 0, 1, 0, 1};
	vector<int> sent2Expected = {1, 1, 1, 0, 1};

	ASSERT_EQ(newSent1->sentence_array, sent1Expected);
	ASSERT_FALSE(newSent1->label);
	ASSERT_TRUE(newSent2->label);
}


TEST_F(test_CountVectorizer, buildSentenceVector) {
	CountVectorizer myCV(true);

	string test_sentence = "This is my test sentence!";
	vector<string> expected1 = {"This", "is", "my", "test", "sentence", "!"};
	ASSERT_EQ(myCV.buildSentenceVector(test_sentence), expected1);

	CountVectorizer myCaseInsCV(false);

	vector<string> expected2 = {"this", "is", "my", "test", "sentence", "!"};
	ASSERT_EQ(myCaseInsCV.buildSentenceVector(test_sentence), expected2);
}


TEST_F(test_CountVectorizer, addSentence) {
	CountVectorizer myCV(true);
	string test_sentence1 = "This is my first sentence!";
	vector<int> expected1 = {1, 1, 1, 1, 1, 1};
	string test_sentence2 = "what is going on";
	vector<int> expected2 = {0, 1, 0, 0, 0, 0, 1, 1, 1};
	myCV.addSentence(test_sentence1, true);
	myCV.addSentence(test_sentence2, false);
	
	ASSERT_EQ(myCV.getSentence(0)->sentence_array, expected1);
	ASSERT_EQ(myCV.getSentence(1)->sentence_array, expected2);
}

TEST_F(test_CountVectorizer, getWeight) {
	CountVectorizer myCV(true);
	string test_sentence1 = "This is my first sentence!";
	// vector<int> expected1 = {1, 1, 1, 1, 1, 1};
	string test_sentence2 = "what is going on";
	// vector<int> expected2 = {0, 1, 0, 0, 0, 0, 1, 1, 1};
	myCV.addSentence(test_sentence1, true);
	myCV.addSentence(test_sentence2, false);
	
	ASSERT_EQ(myCV.getWeight({"This", "is", "going"}), 0.5);
}

TEST_F(test_CountVectorizer, is_wordInSentence) {
	CountVectorizer myCV(true);
	string test_sentence1 = "This is my first sentence!";
	myCV.addSentence(test_sentence1, false);
	ASSERT_EQ(myCV.is_wordInSentence(*(myCV.getSentence(0)), 2), 1);
}

TEST_F(test_CountVectorizer, fullScopeTest) {
	CountVectorizer myCV(false);
	unsigned int data_volume = features.size();
	for (unsigned int i = 0; i < data_volume; i++) {
		myCV.addSentence(features[i], (bool) labels[i]);
	}
	ASSERT_EQ(myCV.analyze("The food was great. Loved it so much!"), POS);
	ASSERT_EQ(myCV.analyze("Just terrible, can't stand it. Won't go back"), NEG);
	ASSERT_EQ(myCV.analyze("THISISAMADEUPSENTENCE"), UNK);
}
