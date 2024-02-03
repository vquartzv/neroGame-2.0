#include "bakteria.h"
#include <iostream>
#include "brain.h"
#include "brain.cpp"

poin::poin(std::pair<int, int> Pos, int genSize, int genomSize, int enerji):pos(Pos), sizGen(genSize), sizGenom(genomSize), Brain(brain(genSize, genomSize)), energi(enerji){
	oritation=std::rand()%4;
}
poin::poin(std::pair<int, int> Pos, int genSize, int genomSize, int enerji, brain br):pos(Pos), sizGen(genSize), sizGenom(genomSize), Brain(br), energi(enerji){
	oritation=std::rand()%4;
}

void poin::ret_left(){
	oritation--;
	if (oritation<0){oritation=3;};
}

void poin::ret_rigth(){
	oritation++;
	if (oritation>3){oritation=0;};
}

std::pair<int, int> poin::getPos(){
	return pos;
}

std::pair<int, int> poin::move(){
	return seePos();
}

int poin::seePlant(){
	return 0;
}

std::pair<int, int> poin::seePos(){
	std::pair<int, int> position= pos;
	position.first+=moveOrintation[oritation][0];
	position.second+=moveOrintation[oritation][1];
	return position;
}

void poin::setPos(std::pair<int, int> Pos){
	pos=Pos;
}

void poin::killUp(){
	if(kill>1){
		kill--;
	};
}

void poin::killDown(){
	if(kill<9){
		kill++;
	};
}

int poin::killGet(){
	return kill;
}