#pragma once 
#include "map.h"
#include "bakteria.h"
#include <vector>
#include <string>
#include "bakteria.h"
#include <SFML/Graphics.hpp>


map::map(int maxX, int maxY):maxX(maxX), maxY(maxY){
	
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