#ifndef BACTERIA_H
#define BACTERIA_H
#include <iostream>
#include <vector>
#include "brain.h"

class poin{
    
    private:
    int kill=5;
    std::pair<int, int> pos;
    int oritation;
    int sizGen, sizGenom;
    const int moveOrintation[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

    
    public:
    poin& operator=(const poin& other) {
        if (this != &other) {
            this->kill = other.kill;
            this->pos = other.pos;
            this->oritation = other.oritation;
            this->sizGen = other.sizGen;
            this->sizGenom = other.sizGenom;
            this->energi = other.energi;
            this->old = other.old;
            this->Brain = other.Brain;
            this->lineage = other.lineage;
        }
        return *this;
    };
    int lineage=0;
    int energi=0;
    int old=0;
    poin(int lineage, std::pair<int, int>, int, int, int);
    poin(int lineage, std::pair<int, int>, int, int, int, brain);
    std::pair<int, int> getPos();
    std::pair<int, int> move();
    int seePlant();
    std::pair<int, int> seePos();
    void setPos(std::pair<int, int>);
    brain Brain;
    void ret_left();
    void ret_rigth();
    void killUp();
    void killDown();
    int killGet();
    int getLineage();
	
	
};

#endif // BACTERIA_H