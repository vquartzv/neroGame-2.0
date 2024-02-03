#ifndef BACTERIA_H
#define BACTERIA_H
#include <iostream>
#include <vector>
#include "brain.h"

class poin{
	public:
	poin& operator=(const poin& other) {
        if (this != &other) {
            // ... ваш код копирования ...
        }
	    return *this;
	};
    int energi=0;
    int old=0;
	poin(std::pair<int, int>, int, int, int);
	poin(std::pair<int, int>, int, int, int, brain);
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
	
	
	private:
	int kill=5;
	std::pair<int, int> pos;
	int oritation;
	int sizGen, sizGenom;
	
	
	const int moveOrintation[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
};

#endif // BACTERIA_H