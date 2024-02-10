#include "bakteria.h"
#include "bakteria.cpp"
#include "map.h"
#include "map.cpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <SFML/Graphics.hpp>

using std::cout;
const int startPoin = 600; 
const int sizeX = 50;
const int sizeY = 50;
const int genSize = 8;
const int genomSize=30;
const int enerjiStart=20;
const int z = 4;
const int maxOld = 100;
const int fotosUp = 5;
const int maxEnerji = 50;
const int enerjiSpawn = 20;
const int iterBrain = 5;
const int runEnergiDel = 2;
const bool logs = false;

bool gameRun = true;
int max_lineage=0;
int mapSee=0;
int sizePoin=10;

void startGetPoin(map* pl){
    for(int i=0; i<startPoin; i++){
        while(true){
            std::pair<int, int> pos = {std::rand()%(sizeX+1), std::rand()%(sizeY+1)};
            if(pl->getObj(pos)==nullptr){
                pl->setObj(pos, poin(max_lineage, pos, genSize, genomSize, enerjiStart));
                max_lineage++;
                break;
            }
        }
    }
}

void movePoint(map* plant, poin* point){
    std::pair<int, int> posSet = point->getPos();
    std::pair<int, int> move = point->move();
    if(move.first>sizeX){move.first=0;}
    else if (move.first<0){move.first=sizeX;};
    if(move.second>sizeY){move.second=0;}
    else if(move.second<0){move.second=sizeY;};
    if(plant->getObj(move)==nullptr){
        plant->plant[move]=plant->plant[posSet];
        plant->plant.erase(posSet);
        if(logs){cout<<"move "<<posSet.first<<":"<<posSet.second<<"\n";};
        point->setPos(move);
        point->energi-=runEnergiDel;
        if(logs){cout<<"move "<<posSet.first<<":"<<posSet.second<<"\n";};
    };
}

void delPoin(map* plant, poin* point, int* dell, std::string text = ""){
    std::pair<int, int> posSet = plant->box[*dell].getPos();
    int set = *dell;
    if(plant->box[set].energi<=0||plant->box[set].old>=maxOld){
        if(posSet==plant->box[*dell].getPos()){
            if(logs){
                cout<<"end "<<text<<": "<<posSet.first<<" "<<posSet.second<<" "<<plant->box.size()<<"\n";
                cout<<"end: "<<text<<": "<<plant->box[*dell].getPos().first<<" "<<plant->box[*dell].getPos().second<<plant->box.size()<<"\n";
            };
            //plant->box.erase(plant->box.begin()+*dell);
            plant->update();
            char g;
            std::cin>>g;
        };
        plant->printPlant();
    };
};

void killPoint(map* plant, poin* point, int* dell){
    std::pair<int, int> posSet = point->getPos();
    std::pair<int, int> move = point->move();
    if(plant->getObj(move)!=nullptr){
        int i=0;
        for (auto a=plant->box.begin()+1; a!=plant->box.end(); i++){
            if(i<*dell){*dell--;};
            if(a->getPos()==move){
                if(logs){
                    cout<<"kill "<<move.first<<":"<<move.second<<"\n";
                    cout<<"kill "<<posSet.first<<":"<<posSet.second<<"\n";
                };
                a = plant->box.erase(a);
                plant->update();
                plant->printPlant();
                return;
            }else{a++;};
        };
    };
};

void spawnPoint(map* plant, poin* point){
    std::pair<int, int> posSet = point->getPos();
    std::pair<int, int> move = point->move();
    if(plant->getObj(move)==nullptr&&point->energi>enerjiSpawn+10&&move.first>=0&&move.first<=sizeX && move.second>=0 && move.second<=sizeY){
        plant->setObj(move, poin(point->lineage, move, genSize, genomSize, enerjiSpawn, brain(genSize, genomSize, point->Brain.dell(z))));
        plant->update();
        point->energi-=enerjiSpawn;
        if(logs){cout<<"spawn "<<posSet.first<<":"<<posSet.second<<"\n";};
        
    };
};

void runBrain(map* plant, poin* point, int* del){
    std::pair<int, int> posSet = point->getPos();
    std::pair<int, int> move = point->move();
    for(int i=0; i<iterBrain; i++){
        int otvet = point->Brain.run();
        switch(otvet){
            case 1:
            movePoint(plant, point);
            plant->update();
            return;
            
            case 2:
            point->ret_rigth();
            plant->update();
            break;
            
            case 3:
            point->ret_left();
            plant->update();
            break;
            
            case 4:
            killPoint(plant, point, del);
            return;
            
            case 5:
            spawnPoint(plant, point);
            plant->update();
            return;
            
            case 6:
            if(point->energi<maxEnerji){
                point->energi+=fotosUp;
            };
            point->killDown();
            plant->update();
            return;
            
            case 7:
            if(plant->getObj(move)!=nullptr){
                point->Brain.moveGenSet(1);
            }else{
                point->Brain.moveGenSet(2);
            };
            break;
            
            case 8:
            if(plant->getObj(move)!=nullptr){
                for(auto a = plant->box.begin(); a!=plant->box.end(); a++){
                    if(a->getPos()==move){
                        if(a->lineage==point->lineage){
                            point->Brain.moveGenSet(1);
                        }
                        else{
                            point->Brain.moveGenSet(2);
                        };
                    };
                };
            };
            
            default:
            return;
        };
    };
};

void createWin(sf::VertexArray* boxdraw){
	sf::RectangleShape rectangle;
    sf::VertexArray grid;
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(mode, "My window", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

	int sizeBoxX=sizeX;
	sizePoin=(window.getSize().x-40)/sizeBoxX;
	int sizeX=window.getSize().x-40;
    
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
    
    while(window.isOpen()){
    	sf::Event event;
    	while (window.pollEvent(event)){
	               if (event.type == sf::Event::Closed){
	               	window.close();
	               	};
	               };
    	window.clear(sf::Color::Blue);
    	window.draw(rectangle);
    	window.draw(grid);
    	//window.draw(*boxdraw);
    	window.display();
    };
};

sf::VertexArray updateMap(map* plant){
	sf::VertexArray squares(sf::Quads, plant->box.size() * 4);
    sf::Color squareColor = sf::Color::Green;
    for(int i = 0; i<plant->box.size(); i++){
        	int x=plant->box[i].getPos().first*sizePoin+20;
        	int y=plant->box[i].getPos().second*sizePoin+20;
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
    return squares;
};

int main(int argc, char *argv[])
{
    map plant = map(sizeX, sizeY);
    sf::VertexArray boxdraw = updateMap(&plant);
    std::thread thre(createWin, &boxdraw);
    thre.detach();
    startGetPoin(&plant);
    int delI = 0;
    for (int c=0; c<100000; c++){
        for(auto a=plant.box.begin(); a!=plant.box.end(); a++){
            a->old++;
        };
        for (auto it = plant.box.begin(); it != plant.box.end(); ) {
            if (it->old > maxOld || it->energi<0) {
                if (logs) {
                    std::pair<int, int> posSet = it->getPos();
                    std::pair<int, int> move = it->move();
                    cout << "end old_max: " << ": " << posSet.first << " " << posSet.second << " " << it->old << "\n";
                }
                it = plant.box.erase(it); // Возвращаем итератор на следующий элемент после удаления
                plant.update();
                if (logs) {
                    plant.printPlant();
                }
            } else {
                ++it; // Переходим к следующему элементу в векторе
            }
        };
        for(int i=plant.box.size()-1; i>=0; i--){
            runBrain(&plant, &plant.box[i], &i);
        };
        if(c%1==0){
                cout<<"\n";
            cout<<"\n";
            cout<<"\n";
                plant.printPlant();
                sf::VertexArray boxdraw = updateMap(&plant);
                //std::this_thread::sleep_for(std::chrono::milliseconds(20));
            };
        if(plant.box.size()==0){
            startGetPoin(&plant);
            char g;
            std::cin>>g;
        };
    };
    cout<<"end:\n";
    plant.printPlant();
}