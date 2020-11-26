#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "bst.h"


class WordMeaning {
        string word;
        string meaning;
public:
        WordMeaning(string w, string m): word(w), meaning(m) {;}
        void setWord(string w) {word=w; }
        void setMeaning(string m) { meaning=m; }
        string getWord() const { return word; }
        string getMeaning() const { return meaning; }
        bool operator < (const WordMeaning &wm1) const;
};

ostream& operator<<(ostream &out, WordMeaning& wm);

class Dictionary{
    BST<WordMeaning> words;
public:
    Dictionary(): words(WordMeaning("","")){};
    BST<WordMeaning> getWords() const;
    void readDictionary(ifstream &f);
    string searchFor(string word) const;
    bool correct(string word, string newMeaning);
    void print() const;
};


//TODO
class WordInexistent{
    WordMeaning before;
    WordMeaning after;
public:
    string getWordBefore() const;
    string getMeaningBefore();
    string getWordAfter();
    string getMeaningAfter();
    WordInexistent(WordMeaning bef, WordMeaning after);
};

#endif