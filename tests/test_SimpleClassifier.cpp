#include <gtest/gtest.h>
#include "../code/SimpleClassifier.h"

#include <iostream>
#include <string>

using namespace std;

class test_SimpleClassifier : public ::testing::Test
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

TEST_F(test_SimpleClassifier, getWeight)
{
	SimpleClassifier mySimple;
	string test_sentence1 = "random";
	string test_sentence2 = "superman";
	mySimple.CV.addSentence(test_sentence1, true);
	mySimple.CV.addSentence(test_sentence2, false);
	ASSERT_EQ(mySimple.getWeight({"random", "superman"}), 0.5);
}

TEST_F(test_SimpleClassifier, fullScopeTest)
{
	SimpleClassifier mySimple;
	MyGlobalVars vars;
	mySimple.fit(vars.features_file, vars.labels_file);
	if (mySimple.CV.getSentence(0))
	{
		ASSERT_EQ(mySimple.analyze("The food was great. Loved it so much!"), vars.POS);
		ASSERT_EQ(mySimple.analyze("Just terrible, can't stand it. Won't go back"), vars.NEG);
		ASSERT_EQ(mySimple.analyze("THISISAMADEUPSENTENCE"), vars.UNK);
	}
}
