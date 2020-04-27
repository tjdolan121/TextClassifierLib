#include "NaiveBayesClassifier.h"

NaiveBayesClassifier::NaiveBayesClassifier(string true_label_meaning_, string false_label_meaning_)
{
    true_label_meaning = true_label_meaning_;
    false_label_meaning = false_label_meaning_;
    CV.setBinary(false);
    CV.setCaseSensitive(false);
    CV.setIncludeStopWords(false);
}

NaiveBayesClassifier::~NaiveBayesClassifier()
{
}

int NaiveBayesClassifier::totalWords()
{
    int ret = 0;
    for (auto sentence : CV.sentences)
    {
        for (auto count_ : sentence->sentence_array)
        {
            ret += count_;
        }
    }
    return ret;
}

int NaiveBayesClassifier::totalWordsOfType(bool label_)
{
    int ret = 0;
    for (auto sentence : CV.sentences)
    {
        for (auto count_ : sentence->sentence_array)
        {
            if (sentence->label == label_)
            {
                ret += count_;
            }
        }
    }
    return ret;
}

float NaiveBayesClassifier::pOfType(bool label_)
{
    int ttl = totalWords();
    int ttlOfType = totalWordsOfType(label_);
    return (float)ttlOfType / (float)ttl;
}

int NaiveBayesClassifier::countOccurances(string word)
{
    int ret = 0;
    unsigned int word_array_size = CV.getWordArraySize();
    for (unsigned int i = 0; i < word_array_size; i++)
    {
        if (CV.word_array[i] == word)
        {
            for (auto sentence : CV.sentences)
            {
                if (sentence->sentence_array.size() > i)
                {
                    ret += sentence->sentence_array[i];
                }
            }
        }
    }
    return ret;
}

int NaiveBayesClassifier::countOccurancesOfType(string word, bool label_)
{
    int ret = 0;
    unsigned int word_array_size = CV.getWordArraySize();
    for (unsigned int i = 0; i < word_array_size; i++)
    {
        if (CV.word_array[i] == word)
        {
            for (auto sentence : CV.sentences)
            {
                if (sentence->sentence_array.size() > i)
                {
                    if (sentence->label == label_)
                    {
                        ret += sentence->sentence_array[i];
                    }
                }
            }
        }
    }
    return ret;
}

float NaiveBayesClassifier::getWeight(vector<string> sentence, bool label_)
{
    int total_words_of_type = totalWordsOfType(label_);
    float mp = smoothing_param_m * smoothing_param_p;
    float m = smoothing_param_m;
    float ret = log(pOfType(label_));
    for (auto word : sentence)
    {
        ret += log(((float)countOccurancesOfType(word, label_) + mp) / ((float)total_words_of_type + m));
    }
    return ret;
}

int NaiveBayesClassifier::analyze(string sentence)
{
    MyGlobalVars vars;
    vector<string> processed_input;
    processed_input = CV.buildSentenceVector(sentence); // Encapsulate better
    float trueWeight = getWeight(processed_input, true);
    float falseWeight = getWeight(processed_input, false);
    if (trueWeight < falseWeight)
    {
        cout << false_label_meaning << endl;
        return vars.NEG;
    }
    else if (trueWeight > falseWeight)
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