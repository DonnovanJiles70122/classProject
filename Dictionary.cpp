//
// Created by Donnovan Jiles on 3/18/21.
//

#include "Dictionary.h"
#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
using namespace std;

Dictionary::Dictionary() = default;

multimap <string, multimap<string, string> > dictionary;
multimap <string, string> partSpeech;
const vector<string> Dictionary::wordClass {"noun", "verb", "adjective", "adverb",
                                            "conjunction", "interjection", "pronoun",
                                            "preposition"};

void Dictionary::parser(multimap<string, multimap<string, string>> &dict, multimap<string, string> &partOfSpeech,
                        string &word, string &line, string &pos, string &def) {
    int space = 5;
    if(line.find('|') == 0)
    {
        string s = line.substr(1);
        parser(dict, partOfSpeech, word, s, pos, def);
    }
    else if(line.find('|') == -1)
    {
        int end = line.find("-=>>");
        pos = line.substr(0, end - 1);
        def = line.substr(end + space);
        capitalize(def);
        partOfSpeech.insert(pair<string, string>(pos, def));
        dict.insert(pair<string, multimap<string, string> >(word, partOfSpeech));
    } else
    {
        int endPos = line.find("-=>>");
        int endDef = line.find('|');
        int defLength = endDef - (endPos + space);
        pos = line.substr(0, endPos - 1);
        def = line.substr(endPos + space, defLength);
        capitalize(def);
        partOfSpeech.insert(pair<string, string>(pos, def));
        string nextDef = line.substr(line.find('|') + 1);
        parser(dict, partOfSpeech,word, nextDef, pos, def);
    }
}

int Dictionary::keyword(multimap<string, multimap<string, string>> &dict) {
    return dict.size();
}

int Dictionary::defCount(multimap<string, multimap<string, string>> &dict) {
    int size = 0;
    for (auto & it : dict){
        for(auto & i : it.second){
            size++;
        }
    }
    return size;
}

void Dictionary::printWord(multimap<string, string> pos, const string& word, bool rev) {
    if(rev) {
        cout << "\t|\n";
        multimap<string, string>::reverse_iterator rit;
        for (rit = pos.rbegin(); rit != pos.rend(); ++rit) {
            cout << "\t" << word << " [" << rit->first << "] : " << rit->second << "\n";
        }
    } else {
        cout << "\t|\n";
        for (auto & po : pos) {
            cout << "\t" << word << " [" << po.first << "] : " << po.second << "\n";
        }
    }
    cout << "\t|\n";
}

void Dictionary::searchWord(multimap<string, multimap<string, string>> &dict, const string &word, const string& input2,
                            const string& input3, const string& input4) {

    if(dict.find(word) != dict.end()) {
        for (auto & it : dict) {
            if (it.first == word) {
                if (count(wordClass.begin(), wordClass.end(), input2)) {
                    if(input3.empty()) {
                        partOfSpeech(it.second, word, input2, false, false);
                    } else if (input3 == "reverse") {
                        if(input4.empty()) {
                            partOfSpeech(it.second, word, input2, true, false);
                        } else if(input4 == "distinct") {
                            partOfSpeech(it.second, word, input2, true, true);
                        } else {
                            searchWord(dict, word, input2, input3, "");
                        }
                    } else if(input3 == "distinct") {
                        if(input4.empty()) {
                            partOfSpeech(it.second, word, input2, false, true);
                        } else if (input4 == "reverse") {
                            partOfSpeech(it.second, word, input2, true, true);
                        } else {
                            searchWord(dict, word, input2, input3, "");
                        }
                    } else {
                        searchWord(dict, word, input2, input4, "");
                    }
                } else if (input2 == "reverse"){
                    if (input3.empty()) {
                        if(input4.empty()) {
                            getDef(dict, word, true, false);
                        } else{
                            searchWord(dict, word, input2, input3, "");
                        }
                    } else if (input3 == "distinct"){
                        if(input4.empty()) {
                            getDef(dict, word, true, true);
                        } else {
                            searchWord(dict, word, input2, input3, "");
                        }
                    } else {
                        searchWord(dict, word, input2, input4, "");
                    }
                } else if(input2 == "distinct"){
                    if(input3.empty()) {
                        if(input4.empty()) {
                            getDef(dict, word, false, true);
                        } else {
                            searchWord(dict, word, input2, input3, "");
                        }
                    } else if(input3 == "reverse"){
                        if(input4.empty()) {
                            getDef(dict, word, true, true);
                        } else {
                            searchWord(dict, word, input2, input3, "");
                        }
                    } else {
                        searchWord(dict, word, input2, input4, "");
                    }
                } else{
                    getDef(dict, word, false, false);
                }
            }
        }
    }
}

bool Dictionary::checkWordExist(multimap<string, multimap<string, string>> &dict, const string& word) {
    bool result = false;
    for (auto & it : dict) {
        if(it.first == word) {
            result = true;
        }
    }
    return result;
}

void Dictionary::getDef(multimap<string, multimap<string, string>> &dict, string word, bool rev, bool dist) {
    for (auto & it : dict) {
        if (it.first == word) {
            capitalize(word);
            if(rev && !dist){
                printWord(it.second, word, true);
            } else if(!rev && !dist) {
                printWord(it.second, word, false);
            }else if(!rev){
                printDistinct(it.second, word, false, true);
            } else {
                printDistinct(it.second, word, true, true);
            }
        }
    }
}

void Dictionary::printDistinct(const multimap<string, string>& pos, string word, bool rev, bool dist) {
    vector<string> distinct;
    capitalize(word);
    for (auto & po : pos) {
        string def = word + " [" + po.first + "] : " + po.second;
        if(!count(distinct.begin(), distinct.end(),def)){
            distinct.push_back(def);
        }
    }
    if(dist && !rev) {
        cout << "\t|\n";
        for (auto &i : distinct) {
            cout << "\t" << i << "\n";
        }
        cout << "\t|\n";
    } else if(dist) {
        cout << "\t|\n";
        for(int i = distinct.size()-1; i >= 0; i--){
            cout << "\t" << distinct.at(i) << endl;
        }
        cout << "\t|\n";
    }
}

void Dictionary::inputError(const string& s, int e) {
    cout << "\t|" << endl;

    if(e == 2) {
        cout << "\t<The entered 2nd parameter '" + s + "' is NOT part of speech.>\n" +
                "\t<The entered 2nd parameter '" + s + "' is NOT 'distinct'.>\n" +
                "\t<The entered 2nd parameter '" + s + "' is NOT 'reverse'.>\n" +
                "\t<The entered 2nd parameter '" + s + "' was disregarded.>\n" +
                "\t<The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>";
    } else if(e == 3) {
        cout << "\t<The entered 3rd parameter '" + s + "' is NOT 'distinct'.>\n" +
                "\t<The entered 3rd parameter '" + s + "' is NOT 'reverse'.>\n" +
                "\t<The entered 3rd parameter '" + s + "' was disregarded.>\n" +
                "\t<The 3rd parameter should be 'distinct' or 'reverse'.>";
    } else if (e == 4) {
        cout << "\t<The entered 4th parameter '" + s + "' is NOT 'reverse'.>\n" +
                "\t<The entered 4th parameter '" + s + "' was disregarded.>\n" +
                "\t<The 4th parameter should be 'distinct' or 'reverse'.>";
    }
    cout << "\n\t|" << endl;
}

void Dictionary::partOfSpeech(const multimap<string, string>& dict, string word, const string& pos, bool rev, bool dist) {
    vector<string> manipulatePOS;
    for (auto &it : dict) {
        if (it.first == pos) {
            capitalize(word);
            if (!rev && !dist) {
                cout << word << " [" << it.first << "] : " << it.second << "\n";
            } else if (rev && !dist) {
                string def = word + " [" + it.first + "] : " + it.second;
                manipulatePOS.push_back(def);
            } else if (dist) {
                string def = word + " [" + it.first + "] : " + it.second;
                if(!count(manipulatePOS.begin(), manipulatePOS.end(),def)){
                    manipulatePOS.push_back(def);
                }
            }
        }
    }
    if(rev && !dist){
        cout << "\t|\n";
        for(int i = manipulatePOS.size()-1; i >= 0; i--){
            cout << "\t" << manipulatePOS.at(i) << endl;
        }
        cout << "\t|\n";
    }
    if(!rev && dist) {
        cout << "\t|\n";
        for (auto &i : manipulatePOS) {
            cout << "\t" << i << "\n";
        }
        cout << "\t|\n";
    }
    else if(rev && dist) {
        cout << "\t|\n";
        for(int i = manipulatePOS.size()-1; i >= 0; i--){
            cout << "\t" << manipulatePOS.at(i) << endl;
        }
        cout << "\t|\n";
    }
}

void Dictionary::convert(string &s) {
    for(char & i : s){
        i = tolower(i);
    }
}

void Dictionary::capitalize(string &s) {
    s[0] = toupper(s[0]);
}

void Dictionary::printHowTo() {
    cout << "\t|\n"
            "\tPARAMETER HOW-TO, please enter:\n"
            "\t1. A search key -then 2. An optional part of speech -then \n"
            "\t3. An optional 'distinct' -then 4. An optional 'reverse'\n"
            "\t|\n";
}

void Dictionary::printNotFound() {
    cout << "\t|\n\t<NOT FOUND> To be considered for the next release. Thank you.\n\t|\n";
}

vector<string> Dictionary::makeSentence(const string &w) {
    string test;
    vector<string> wordVector;
    for(char i : w)
    {
        if(i != ' ')
            test += i;
        else {
            convert(test);
            wordVector.push_back(test);
            test = "";
        }
    }
    convert(test);
    wordVector.push_back(test);
    return wordVector;
}

void Dictionary::populateDict() {
    fstream dataFile;
    string line;
    cout << "! Loading data...\n";
    dataFile.open("Data.CS.SFSU.txt", ios::in);
    if(!dataFile.is_open())
    {
        cout << "File didn't open program will end in 5 seconds\n";
        exit(EXIT_FAILURE);
    }

    while(getline(dataFile, line))
    {
        partSpeech.clear();
        string word = line.substr(0, line.find('|'));
        string pos, def;
        string next = line.substr(line.find('|') + 1);
        parser(dictionary, partSpeech, word, next, pos, def);
    }
}

void Dictionary::menu() {
    string word;
    vector<string> words;
    int search = 1;
    cout << "! Loading completed...\n\n"
         << "===== DICTIONARY 340 JAVA =====\n"
         << "----- Keywords: " << keyword(dictionary) << "\n"
         << "----- Definitions: " << defCount(dictionary) << "\n";

    while(word != "!q") {
        cout << "Search [" << search << "]: ";
        search++;
        getline(cin, word);
        words = makeSentence(word);

        if(words.size() == 1) {
            if(word=="!help") {
                printHowTo();
            }
            else if(words[0] == "!q")
            {
                cout << "-----THANK YOU-----" << endl;
                exit(1);
            }else {
                if(!checkWordExist(dictionary, words[0])) {
                    printNotFound();
                } else {
                    getDef(dictionary, words[0], false, false);
                }
            }
        } else if(words.size() == 2) {
            checkWordError(words[0], words[1], "", "");
            searchWord(dictionary, words[0], words[1],"", "");
        }
        else if(words.size() == 3){
            checkWordError(words[0], words[1], words[2], "");
            searchWord(dictionary, words[0], words[1], words[2], "");

        }
        else if(words.size() == 4) {
            checkWordError(words[0], words[1], words[2], words[3]);
            searchWord(dictionary, words[0], words[1], words[2], words[3]);
        }
        else{
            printHowTo();
        }
    }
}

bool Dictionary::contains(const string &POS) {
    bool result = false;
    for(auto & x : wordClass){
        if (x == POS) {
            result = true;
            break;
        }
    }
    return result;
}

void Dictionary::checkWordError(const string& word, const string& i2, const string& i3, const string& i4){

    if(!contains(i2))
        if (i2 != "reverse")
            if (i2 != "distinct")
                if (!i2.empty())
                    inputError(word, 2);

    if (i3 != "distinct")
        if (i3 != "reverse")
            if (!i3.empty())
                inputError(word, 3);

    if (i4 != "distinct")
        if (i4 != "reverse")
            if (!i4.empty())
                inputError(word, 4);
}