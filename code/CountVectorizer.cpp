#include "CountVectorizer.h"

using namespace std;

// ================================================================|
// ======================CONSTRUCTORS==============================|
// ================================================================|

CountVectorizer::CountVectorizer()
{
    binary = true;
    case_sensitive = true;
    include_stopwords = true;
}

CountVectorizer::CountVectorizer(bool binary_, bool case_sensitive_, bool include_stopwords_)
{
    binary = binary_;
    case_sensitive = case_sensitive_;
    include_stopwords = include_stopwords_;
}

CountVectorizer::~CountVectorizer()
{
}

// ===============================================================|
// ======================USER INTERFACE FUNCTIONS=================|
// ===============================================================|


void CountVectorizer::fit(string abs_filepath_to_features, string abs_filepath_to_labels)
{
    ifstream in;
    string feature_output;
    string label_output;
    vector<string> features;
    vector<bool> labels;

    in.open(abs_filepath_to_features);

    if (!in)
    {
        cout << "ERROR: Cannot open features file.\n";
        return;
    }

    while (getline(in, feature_output))
    {
        features.push_back(feature_output);
    }
    in.close();

    in.open(abs_filepath_to_labels);

    if (!in)
    {
        cout << "ERROR: Cannot open labels file.\n";
        return;
    }

    while (getline(in, label_output))
    {
        labels.push_back((bool)std::stoi(label_output));
    }
    in.close();

    unsigned int feature_size = features.size();
    if (feature_size != labels.size())
    {
        cout << "ERROR: Feature dimension is different from label dimension\n";
        return;
    }
    for (unsigned int i = 0; i < feature_size; i++)
    {
        addSentence(features[i], labels[i]);
    }
}

void CountVectorizer::shape()
{
    unsigned int wordArraySize = getWordArraySize();
    unsigned int sentenceCount = getSentenceCount();
    cout << "------------------------------" << endl;
    cout << "Current CountVectorizer Shape:" << endl;
    cout << "Total unique words: " << to_string(wordArraySize) << endl;
    cout << "Documents in corpus: " << to_string(sentenceCount) << endl;
    cout << "------------------------------" << endl;
}

void CountVectorizer::head()
{
    int count = 0;
    unsigned int wordArraySize = getWordArraySize();
    if (wordArraySize > 10)
    {
        wordArraySize = 10;
    }
    cout << "------------------------------" << endl;
    cout << "Current CountVectorizer Head:" << endl;
    for (unsigned int i = 0; i < wordArraySize; i++)
    {
        for (auto sentence : sentences)
        {
            if (is_wordInSentence(*sentence, i))
            {
                count++;
            }
        }
        cout << getWord(i) << ": " << count << endl;
        count = 0;
    }
    cout << "------------------------------" << endl;
}

// ===========================================================|
// ======================HELPERS==============================|
// ===========================================================|


int CountVectorizer::is_wordInSentence(Sentence sentence_, unsigned int idx)
{
    return (sentence_.sentence_array.size() > idx && sentence_.sentence_array[idx]);
}

void CountVectorizer::pushSentenceToWordArray(vector<string> new_sentence_vector)
{
    for (string word : new_sentence_vector)
    {
        if (!CountVectorizerContainsWord(word))
        {
            word_array.push_back(word);
        }
    }
}

shared_ptr<Sentence> CountVectorizer::createSentenceObject(vector<string> new_sentence_vector, bool label_)
{
    shared_ptr<Sentence> new_sentence(new Sentence);
    unsigned int word_array_size = getWordArraySize();
    for (unsigned int i = 0; i < word_array_size; i++)
    {
        int count_ = count(new_sentence_vector.begin(), new_sentence_vector.end(), word_array[i]);
        if (count_)
        {
            if (binary)
            {
                new_sentence->sentence_array.push_back(1);
            }
            else
            {
                new_sentence->sentence_array.push_back(count_);
            }
        }
        else
        {
            new_sentence->sentence_array.push_back(0);
        }
    }
    new_sentence->label = label_;
    return new_sentence;
}

void CountVectorizer::addSentence(string new_sentence, bool label_)
{
    vector<string> processedString;
    processedString = buildSentenceVector(new_sentence);
    pushSentenceToWordArray(processedString);
    shared_ptr<Sentence> sentObj = createSentenceObject(processedString, label_);
    sentences.push_back(sentObj);
}

bool CountVectorizer::CountVectorizerContainsWord(string word_to_check)
{
    for (string word : word_array)
    {
        if (word == word_to_check)
        {
            return true;
        }
    }
    return false;
}

vector<string> CountVectorizer::buildSentenceVector(string sentence_)
{
    MyGlobalVars vars;
    string new_word = "";
    vector<string> ret;

    for (char x : sentence_)
    {
        if (isupper(x) && !case_sensitive)
        {
            x = tolower(x);
        }
        if (x == ' ')
        {
            if (!include_stopwords && vars.stopWords.count(new_word))
            {
                new_word = "";
            }
            else
            {
                ret.push_back(new_word);
                new_word = "";
            }
        }
        else if (vars.punctuation.count(x))
        {
            ret.push_back(new_word);
            string s(1, x);
            ret.push_back(s);
            new_word = "";
        }
        else
        {
            new_word = new_word + x;
        }
    }
    if (new_word != "")
    {
        ret.push_back(new_word);
    }
    return ret;
}
