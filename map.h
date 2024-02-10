#ifndef MAP_H
#define MAP_H
#include <map>
#include <vector>
#include "bakteria.h"
#include <string>
#include <SFML/Graphics.hpp>


class map{
    public:
    map(int, int);
    void setObj(std::pair<int, int>, poin);
    poin* getObj(std::pair<int, int>);
    void printPlant();
    std::vector<poin> box;
    std::map<std::pair<int, int>, poin*> plant;
    void update();
    void getWin(int);
    void drawWin();
    
	
    private:
    sf::RenderWindow window;
    int mapSee;
    int maxX;
    int maxY;
    int sizePoin;
    int sizeBoxX;
    int sizeX;
    sf::RectangleShape rectangle;
    sf::VertexArray grid;
    
 };

#endif MAP_H