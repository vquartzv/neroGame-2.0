#pragma once 
#include "map.h"
#include "bakteria.h"
#include <vector>
#include <string>


map::map(int maxX, int maxY):maxX(maxX), maxY(maxY), mapSee(0){
	
}

void map::setObj(std::pair<int, int> pos, poin get){
    srand(static_cast<unsigned int>(time(0)));
    box.push_back(get);
    plant[pos]=&box[-1];
}

poin* map::getObj(std::pair<int, int> pos){
    auto it = plant.find(pos);
    if(it!=plant.end()){
        poin* ret = static_cast<poin*>(it->second);
        return ret;
    }
    else{
        return nullptr;
    };
}

void map::printPlant(){
    std::string draw;
    for(int y=0; y<maxY+1; y++){
        for(int x=0; x<maxX+1; x++){
            poin* see = getObj({x, y});
            if(see!=nullptr){
                if(mapSee==0){
                    draw.append("0");
                }
                else if (mapSee == 1){
                    draw.append(std::to_string(see->killGet()));
                }
                else if (mapSee == 2){
                    int dr = see->energi/20;
                    if(dr<0){
                        draw.append("-");
                    }else{
                        draw.append(std::to_string(dr));
                    }
                }
                else if (mapSee == 3){
                    draw.append(std::to_string(see->old/11));
                }
                else if (mapSee == 4){
                    draw.append(std::to_string(see->lineage/10));
                };
            }
            else{
                draw.append("°");
            };
        };
        draw.append("\n");
    };
    std::cout<<draw;
}

void map::update(){
    plant.clear();
    for(int i=0; i<box.size(); i++){
        plant[box[i].getPos()]=&box[i];
    };
};

void map::getWin(int size){
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	window.create(mode, "My window", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    sizeBoxX=size;
    sizePoin=(window.getSize().x-40)/sizeBoxX;
    sizeX=window.getSize().x-40;
    rectangle.setSize(sf::Vector2f(sizeX, sizeX));
	rectangle.setPosition(20, 20);
	grid.setPrimitiveType(sf::Lines);
	sf::Color gridColor = sf::Color::Black;
	for (int y = 20; y <= sizeX; y += sizePoin)
    {
        // добавляем две вершины для каждой линии
        grid.append(sf::Vertex(sf::Vector2f(20, y), gridColor)); // левый конец линии
        grid.append(sf::Vertex(sf::Vector2f(window.getSize().x-20, y), gridColor)); // правый конец линии
    }
    for (int x = 20; x <= sizeX; x += sizePoin)
    {
        // добавляем две вершины для каждой линии
        grid.append(sf::Vertex(sf::Vector2f(x, 20), gridColor)); // верхний конец линии
        grid.append(sf::Vertex(sf::Vector2f(x, sizeX+20), gridColor)); // нижний конец линии
    }
};

void map::drawWin(){
	sf::Color color = sf::Color::Green;
	sf::Event event;
	
	while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Blue);
        window.draw(rectangle);
        window.draw(grid);
        sf::VertexArray squares(sf::Quads, box.size() * 4);
        sf::Color squareColor = sf::Color::Green;
        for(int i = 0; i<=box.size(); i++){
        	int x=box[i].getPos().first*sizePoin+20;
        	int y=box[i].getPos().second*sizePoin+20;
        	squares[i * 4].position = sf::Vector2f(x, y); // левый верхний угол
        	squares[i * 4 + 1].position = sf::Vector2f(x + sizePoin, y); // правый верхний угол
        	squares[i * 4 + 2].position = sf::Vector2f(x + sizePoin, y + sizePoin); // правый нижний угол
        	squares[i * 4 + 3].position = sf::Vector2f(x, y + sizePoin); // левый нижний угол
        	if(mapSee==0){
        		squareColor = sf::Color::Green;
        	};
        	squares[i * 4].color = squareColor;
        	squares[i * 4 + 1].color = squareColor;
        	squares[i * 4 + 2].color = squareColor;
        	squares[i * 4 + 3].color = squareColor;
        };
        window.draw(squares);
        window.display();
};