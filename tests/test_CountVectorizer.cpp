#include <gtest/gtest.h>
#include "../code/CountVectorizer.h"

#include <iostream>
#include <string>

using namespace std;

class test_CountVectorizer : public ::testing::Test
{
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase()
	{
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase()
	{
	}

	// this function runs before every TEST_F function
	void SetUp() override
	{
	}

	// this function runs after every TEST_F function
	void TearDown() override
	{
	}
};

TEST_F(test_CountVectorizer, pushSentenceToWordArray)
{

	CountVectorizer myCV;
	MyGlobalVars vars;
	myCV.pushSentenceToWordArray(vars.sent1);
	// | This | is | my | new | sentence |

	ASSERT_EQ(myCV.getWord(0), "This");
	ASSERT_EQ(myCV.getWord(3), "new");
	ASSERT_EQ(myCV.getWordArraySize(), 5);

	myCV.pushSentenceToWordArray(vars.sent2);
	// | This | is | my | new | sentence | this | cat |

	ASSERT_EQ(myCV.getWord(5), "this");
	ASSERT_EQ(myCV.getWord(6), "cat");
	ASSERT_EQ(myCV.getWord(7), "!");
	ASSERT_EQ(myCV.getWordArraySize(), 8);
}

TEST_F(test_CountVectorizer, createSentenceObject)
{

	CountVectorizer myCV;
	MyGlobalVars vars;
	myCV.pushSentenceToWordArray(vars.sent1);
	// | This | is | my | new | sentence |

	shared_ptr<Sentence> newSent1;
	newSent1 = myCV.createSentenceObject({"my", "sentence"}, false);
	// sentence array = | 0 | 0 | 1 | 0 | 1 |   label = false

	shared_ptr<Sentence> newSent2;
	newSent2 = myCV.createSentenceObject({"This", "is", "my", "sentence"}, true);
	// sentence array = | 1 | 1 | 1 | 0 | 1 |   label = true

	vector<int> sent1Expected = {0, 0, 1, 0, 1};
	vector<int> sent2Expected = {1, 1, 1, 0, 1};

	ASSERT_EQ(newSent1->sentence_array, sent1Expected);
	ASSERT_FALSE(newSent1->label);
	ASSERT_TRUE(newSent2->label);
}

TEST_F(test_CountVectorizer, createSentenceObjectBinaryFalse)
{
	CountVectorizer myCV(false, true, true);
	MyGlobalVars vars;
	myCV.pushSentenceToWordArray(vars.sent3);
	shared_ptr<Sentence> newSent1;
	newSent1 = myCV.createSentenceObject(vars.sent3, true);
	vector<int> sent1Expected = {3, 2, 1};
	ASSERT_EQ(newSent1->sentence_array, sent1Expected);
}

TEST_F(test_CountVectorizer, buildSentenceVector)
{
	CountVectorizer myCV;

	string test_sentence = "This is my test sentence!";
	vector<string> expected1 = {"This", "is", "my", "test", "sentence", "!"};
	ASSERT_EQ(myCV.buildSentenceVector(test_sentence), expected1);

	CountVectorizer myCaseInsCV(true, false, true);

	vector<string> expected2 = {"this", "is", "my", "test", "sentence", "!"};
	ASSERT_EQ(myCaseInsCV.buildSentenceVector(test_sentence), expected2);
}

TEST_F(test_CountVectorizer, buildSentenceVectorNoStopWords)
{
	CountVectorizer myCV(true, true, false);

	string test_sentence = "This is my test sentence!";
	vector<string> expected1 = {"test", "sentence", "!"};
	ASSERT_EQ(myCV.buildSentenceVector(test_sentence), expected1);
}

TEST_F(test_CountVectorizer, addSentence)
{
	CountVectorizer myCV;
	string test_sentence1 = "This is my first sentence!";
	vector<int> expected1 = {1, 1, 1, 1, 1, 1};
	string test_sentence2 = "what is going on";
	vector<int> expected2 = {0, 1, 0, 0, 0, 0, 1, 1, 1};
	myCV.addSentence(test_sentence1, true);
	myCV.addSentence(test_sentence2, false);

	ASSERT_EQ(myCV.getSentence(0)->sentence_array, expected1);
	ASSERT_EQ(myCV.getSentence(1)->sentence_array, expected2);
}

TEST_F(test_CountVectorizer, getWeight)
{
	CountVectorizer myCV;
	string test_sentence1 = "This is my first sentence!";
	string test_sentence2 = "what is going on";
	myCV.addSentence(test_sentence1, true);
	myCV.addSentence(test_sentence2, false);
	ASSERT_EQ(myCV.getWeight({"This", "is", "going"}), 0.5);
}

TEST_F(test_CountVectorizer, is_wordInSentence)
{
	CountVectorizer myCV;
	string test_sentence1 = "This is my first sentence!";
	myCV.addSentence(test_sentence1, false);
	ASSERT_EQ(myCV.is_wordInSentence(*(myCV.getSentence(0)), 2), 1);
}

TEST_F(test_CountVectorizer, fit)
{
	CountVectorizer myCV;
	MyGlobalVars vars;
	vector<int> expected1 = {1, 1, 1, 1};
	vector<int> expected2 = {0, 0, 0, 0, 1, 1, 1, 1};
	myCV.fit(vars.features_file, vars.labels_file);
	if (myCV.getSentence(0))
	{
		ASSERT_EQ(myCV.getSentence(0)->sentence_array, expected1);
		ASSERT_EQ(myCV.getSentence(1)->sentence_array, expected2);
		ASSERT_TRUE(myCV.getSentence(0)->label);
		ASSERT_FALSE(myCV.getSentence(1)->label);
	}
}

TEST_F(test_CountVectorizer, fullScopeTest)
{
	CountVectorizer myCV(true, false, true);
	MyGlobalVars vars;
	myCV.fit(vars.features_file, vars.labels_file);
	if (myCV.getSentence(0))
	{
		ASSERT_EQ(myCV.analyze("The food was great. Loved it so much!"), vars.POS);
		ASSERT_EQ(myCV.analyze("Just terrible, can't stand it. Won't go back"), vars.NEG);
		ASSERT_EQ(myCV.analyze("THISISAMADEUPSENTENCE"), vars.UNK);
	}
}
