//
// Created by Donnovan Jiles on 3/18/21.
//

#ifndef ASS3_DICTIONARY_H
#define ASS3_DICTIONARY_H
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

class Dictionary {
public:
    Dictionary();
    static vector<string> makeSentence(const string& w);
    void parser(multimap <string, multimap<string, string>> &dictionary,
                multimap<string, string> &partOfSpeech,
                string &word, string &line, string &pos, string &def);
    static void printWord(multimap<string, string> pos, const string& word, bool rev);
    void searchWord(multimap <string, multimap<string, string>> &dict, const string& word, const string& input2, const string& input3, const string& input4);
    static void getDef(multimap <string, multimap<string, string>> &dict, string word, bool rev, bool dist);
    static void printDistinct(const multimap<string, string>& pos, string word, bool rev, bool dist);
    static void inputError(const string& s, int e);
    static void partOfSpeech(const multimap<string, string>& dict, string word, const string& pos, bool rev, bool dist);
    static void convert(string& s);
    static void capitalize(string &s);
    static void printHowTo();
    static void printNotFound();
    static int keyword(multimap<string, multimap<string, string>> &dictionary);
    static int defCount(multimap<string, multimap<string, string>> &dict);
    static const vector<string> wordClass;
    void populateDict();
    void menu();
    static void checkWordError(const string& word, const string& i2, const string& i3, const string& i4);
    static bool checkWordExist(multimap<string, multimap<string, string>> &dict, const string& word);

    static bool contains(const string &POS);
};


#endif //ASS3_DICTIONARY_H
