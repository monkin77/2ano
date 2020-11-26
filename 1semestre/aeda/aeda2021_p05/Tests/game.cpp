#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}

// TODO
Game::Game(){
    ;
}

// TODO
Game::Game(list<Kid>& l2){
    this->kids = l2;
}

// TODO
void Game::addKid(const Kid &k1){
    this->kids.push_back(k1);
}

// TODO
list<Kid> Game::getKids() const{
    return this->kids;
}

// TODO
string Game::write() const{
    string res = "";
    //list<Kid>::iterator it;
    for(auto it = this->kids.begin(); it != this->kids.end(); it++){
        res += it->write() + "\n";
    }

    return res;
}

// TODO
Kid& Game::loseGame(string phrase){
    Kid *k1 = new Kid();
    list<Kid> copy = this->kids;
    auto it = copy.begin();
    int no_words = this->numberOfWords(phrase);
    while(copy.size() > 1){
        //cout << "New Round --" << endl;
        int size = copy.size();
        for(int i = 0; i < no_words; i++){
            if(i % size == 0)
                it = copy.begin();
            else
                it++;
            //cout << "Person:" << (*it).getName() << endl;
        }
        copy.remove(*it);
    }
    it = copy.begin();
    *k1 = (*it);
    return *k1;
}

// TODO
list<Kid>& Game::reverse(){
    this->kids.reverse();   // linear algorithm O(n)
    return this->kids;
}

// TODO
list<Kid> Game::removeOlder(unsigned id){
    list<Kid> res;
    for(auto iter = this->kids.begin(); iter != this->kids.end(); iter++){
        if( iter->getAge() > id ){
            res.push_back(*iter);
            this->kids.remove(*iter);
        }
    }
    return res;
}

// TODO
void Game::setKids(const list<Kid>& l1){
    this->kids = l1;
}

// TODO
bool Game::operator==(Game& g2){
	auto it1 = this->kids.begin();
	auto it2 = g2.getKids().begin();
	while(it1 != this->kids.end()){
	    if( (*it1) == (*it2)){
            it1++;
            it2++;
	    }
	    else
	        return false;

	}
	return true;
}

// TODO
list<Kid> Game::shuffle() const{
    srand(time(NULL));
    list<Kid> res;
    int randomIdx;
    auto idxIt = res.begin();
    for(auto it = this->kids.begin(); it != this->kids.end(); it++){
        idxIt = res.begin();
        if(res.empty())
            randomIdx = 0;
        else
            randomIdx = rand() % res.size();

        //iterator to point to the begin + randomIdx position
        advance(idxIt, randomIdx);
        cout << "New elem at pos " << randomIdx << " " << it->getName() << endl;
        res.insert(idxIt, (*it));
    }

    return res;
}
