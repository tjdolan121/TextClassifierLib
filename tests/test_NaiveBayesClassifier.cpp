#include <gtest/gtest.h>
#include "../code/NaiveBayesClassifier.h"

#include <iostream>
#include <string>

using namespace std;

class test_NaiveBayesClassifier : public ::testing::Test
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

TEST_F(test_NaiveBayesClassifier, totalWords)
{
    NaiveBayesClassifier myBayes;
    myBayes.CV.addSentence("random monkey string funky", true);
    myBayes.CV.addSentence("another funky report", false);
    int ttl = myBayes.totalWords();
    ASSERT_EQ(ttl, 7);
}

TEST_F(test_NaiveBayesClassifier, totalWordsOfType)
{
    NaiveBayesClassifier myBayes;
    myBayes.CV.addSentence("random monkey string funky", true);
    myBayes.CV.addSentence("another funky report", false);
    int ttl_true = myBayes.totalWordsOfType(true);
    int ttl_false = myBayes.totalWordsOfType(false);
    ASSERT_EQ(ttl_true, 4);
    ASSERT_EQ(ttl_false, 3);
}

TEST_F(test_NaiveBayesClassifier, pOfType)
{
    NaiveBayesClassifier myBayes;
    myBayes.CV.addSentence("random monkey string can if they same", true);
    myBayes.CV.addSentence("another funky report", false);
    float p_true = myBayes.pOfType(true);
    float p_false = myBayes.pOfType(false);
    float expected_true = 0.7;
    float expected_false = 0.3;
    float epsilon = .0001;
    ASSERT_TRUE(abs(p_true - expected_true) < epsilon);
    ASSERT_TRUE(abs(p_false - expected_false) < epsilon);
}

TEST_F(test_NaiveBayesClassifier, countOccurances)
{
    NaiveBayesClassifier myBayes;
    myBayes.CV.addSentence("random monkey random day", true);
    myBayes.CV.addSentence("another funky random", false);
    ASSERT_EQ(myBayes.countOccurances("random"), 3);
    ASSERT_EQ(myBayes.countOccurances("band"), 0);
}



TEST_F(test_NaiveBayesClassifier, fullScopeTest)
{
	NaiveBayesClassifier myBayes;
	MyGlobalVars vars;
	myBayes.fit(vars.features_file, vars.labels_file);
    cout << "loved " << myBayes.countOccurances("loved") << endl;
	if (myBayes.CV.getSentence(0))
	{
		ASSERT_EQ(myBayes.analyze("The food was great. Loved it so much!"), vars.POS);
		ASSERT_EQ(myBayes.analyze("Just terrible, can't stand it. Won't go back"), vars.NEG);
	}
}