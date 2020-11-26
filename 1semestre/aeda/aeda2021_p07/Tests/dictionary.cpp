#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}

//TODO
bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return this->word < wm1.word;
}

//TODO
void Dictionary::readDictionary(ifstream &f){
    string word, meaning;
    while(getline(f, word)){
        getline(f, meaning);
        WordMeaning wm(word, meaning);
        this->words.insert(wm);
    }
}

//TODO
string Dictionary::searchFor(string word) const{
    string wordBef, meaningBef, wordAfter, meaningAfter;
    bool foundAfter = false;
    for(auto it = this->words.begin(); it!= this->words.end(); it++){
        if( (*it).getWord() == word ){
            return (*it).getMeaning();
        }
        if( (*it).getWord() < word ){
            wordBef = (*it).getWord();
            meaningBef = (*it).getMeaning();
            wordAfter = (*it).getWord();
            meaningAfter = (*it).getMeaning();
        }
        else if( ((*it).getWord() > word ) & !foundAfter){
            wordAfter = (*it).getWord();
            meaningAfter = (*it).getMeaning();
            foundAfter = true;
        }
    }
    WordMeaning before(wordBef, meaningBef);
    WordMeaning after(wordAfter, meaningAfter);
    throw WordInexistent(before, after);
}

//TODO
bool Dictionary::correct(string word, string newMeaning){
    WordMeaning wm(word, newMeaning);
    if( this->words.find(wm).getWord().empty() ){       // word not found
        this->words.insert(wm);
        return false;
    }
    this->words.remove(wm);
    this->words.insert(wm);     //when you try to insert an element that already exists it does nothing
    return true;
}

//TODO
void Dictionary::print() const{
    this->words.printTree();
}

ostream& operator<<(ostream &out, WordMeaning& wm){
    out << wm.getWord() << endl << wm.getMeaning();
    return out;
}

WordInexistent::WordInexistent(WordMeaning bef, WordMeaning after) : before(bef), after(after) {}

string WordInexistent::getMeaningAfter() {
    return this->after.getMeaning();
}

string WordInexistent::getWordAfter() {
    return this->after.getWord();
}

string WordInexistent::getMeaningBefore() {
    return this->before.getMeaning();
}

string WordInexistent::getWordBefore() const {
    return this->before.getWord();
}