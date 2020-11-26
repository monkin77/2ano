#include "game.h"
#include <sstream>


//TODO
ostream &operator << (ostream &os, Circle &c1)
{
	return os;
}


//TODO
Game::Game(int h, vector<int> &points, vector<bool> &states) : game( startGame(0, h, points, states) ) {;}  //builds the tree by recursion

BinaryTree<Circle> Game::startGame(int pos, int h, vector<int> &points, vector<bool> &states) {
    Circle c1(points[pos], states[pos]);
    if(h == 0)          // Se estiver nas folhas, retornar binary tree com essa folha
        return BinaryTree<Circle>(c1);

    BinaryTree<Circle> leftTree = startGame(2*pos + 1, h-1, points, states);    //criar binary tree com o nó pai (c1) e folhas por recursao
    BinaryTree<Circle> rightTree = startGame(2*pos +2, h-1, points, states);

    return BinaryTree<Circle>(c1, leftTree, rightTree);
}


//TODO
string Game::writeGame(){
	string ans = "";
	BTItrLevel<Circle> it(this->game);
    while(!it.isAtEnd()){
        ans += to_string(it.retrieve().getPoints() ) + "-";
        if(it.retrieve().getState())
            ans += "true-";
        else
            ans += "false-";
        ans += to_string(it.retrieve().getNVisits()) + "\n";
        it.advance();
    }
    return ans;
}


//TODO
int Game::move(){
	BTItrLevel<Circle> it(this->game);
	int pos = 1, points=-1;
	int n;
	while(!it.isAtEnd()){
        if( it.retrieve().getState() == false ) // ir para a esquerda
            n = pos;
        else                                    // ir para a direita
            n = pos + 1;
        it.retrieve().changeState();
        it.retrieve().incNVisits();
        points = it.retrieve().getPoints();
        int i = 0;
        while(i < n && !it.isAtEnd()){
            it.advance();
            i++;
        }
        pos += n;
	}
	return points;
}


//TODO
int Game::mostVisited(){
	int mostVisits = 0;
	BTItrLevel<Circle> it(this->game);
	if(!it.isAtEnd())
	    it.advance();
	while(!it.isAtEnd()){
	    if(it.retrieve().getNVisits() > mostVisits)
	        mostVisits = it.retrieve().getNVisits();
        it.advance();
	}
	return mostVisits;
}
