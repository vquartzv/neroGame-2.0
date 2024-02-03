#ifndef MAP_H
#define MAP_H
#include <map>
#include <vector>
#include "bakteria.h"
#include <string>


class map{
	public:
	map(int, int);
	void setObj(std::pair<int, int>, poin);
	poin* getObj(std::pair<int, int>);
	void printPlant();
	std::vector<poin> box;
	std::map<std::pair<int, int>, poin*> plant;
	void update();
	
	private:
	int mapSee;
	int maxX;
	int maxY;
};

#endif MAP_H