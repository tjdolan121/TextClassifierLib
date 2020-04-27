#include "SimpleClassifier.h"

SimpleClassifier::SimpleClassifier(string true_label_meaning_, string false_label_meaning_)
{
    true_label_meaning = true_label_meaning_;
    false_label_meaning = false_label_meaning_;
    CV.setBinary(true);
    CV.setCaseSensitive(false);
    CV.setIncludeStopWords(false);
}

SimpleClassifier::~SimpleClassifier()
{
}

int SimpleClassifier::analyze(string sentence)
{
    MyGlobalVars vars;
    vector<string> processed_input;
    float weight = 0;
    processed_input = CV.buildSentenceVector(sentence);
    weight = getWeight(processed_input);
    if (weight == -1)
    {
        cout << "Sorry, not enough data for this input." << endl;
        return vars.UNK;
    }
    else if (weight < .5)
    {
        cout << false_label_meaning << endl;
        return vars.NEG;
    }
    else if (weight > .5)
    {
        cout << true_label_meaning << endl;
        return vars.POS;
    }
    else
    {
        cout << "neutral" << endl;
        return vars.NEU;
    }
}

float SimpleClassifier::getWeight(vector<string> sentence_)
{
    float count = 0;
    float num = 0;
    float sum = 0;
    vector<float> word_weights;
    unsigned int word_array_length = CV.word_array.size();
    for (string queryWord : sentence_)
    {
        for (unsigned int i = 0; i < word_array_length; i++)
        {
            if (queryWord == CV.getWord(i))
            {
                for (auto sentence : CV.sentences)
                {
                    if (CV.is_wordInSentence(*sentence, i))
                    {
                        count += 1;
                        num += sentence->label;
                    }
                }
                float word_weight = num / count;
                word_weights.push_back(word_weight);
                count = 0;
                num = 0;
            }
        }
    }
    float foundOccurances = (float)word_weights.size();
    if (!foundOccurances)
    {
        return -1.0;
    }
    else
    {
        for (float wordWeight : word_weights)
        {
            sum += wordWeight;
        }
    }
    return sum / foundOccurances;
}