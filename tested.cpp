#include "bakteria.h"
#include "bakteria.cpp"
#include "map.h"
#include "map.cpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>

using std::cout;
const int startPoin = 16; 
const int sizeX = 4;
const int sizeY = 4;
const int genSize = 8;
const int genomSize=20;
const int enerjiStart=20;
const int z = 4;
const int maxOld = 100;
const int fotosUp = 10;
const int maxEnerji = 100;
const int enerjiSpawn = 20;
const int iterBrain = 5;
const int runEnergiDel = 2;
const bool logs = true;

bool gameRun = true;

void startGetPoin(map* pl){
		for(int i=0; i<startPoin; i++){
			while(true){
				std::pair<int, int> pos = {std::rand()%(sizeX+1), std::rand()%(sizeY+1)};
				if(pl->getObj(pos)==nullptr){
					pl->setObj(pos, poin(pos, genSize, genomSize, enerjiStart));
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
			point->setPos(move);
			    point->energi-=runEnergiDel;
			    if(logs){cout<<"move "<<posSet.first<<":"<<posSet.second<<"\n";
			        cout<<"move "<<move.first<<":"<<move.second<<"\n";
			    };
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
	for (int a=0; a<plant->box.size(); a++){
				if(plant->box[a].getPos()==move){
					if(a<*dell){
						*dell-=1;
					};
					plant->plant.erase((plant->box[a].getPos()));
					plant->box.erase((plant->box.begin()+a));
				    if(logs){
				        cout<<"kill "<<posSet.first<<":"<<posSet.second<<plant->box[a].old<<"\n";
				        cout<<"kill "<<move.first<<":"<<move.second<<"\n";
				    };
					break;
				};
			};
	};
};

void spawnPoint(map* plant, poin* point){
	std::pair<int, int> posSet = point->getPos();
	std::pair<int, int> move = point->move();
	if(plant->getObj(move)==nullptr&&point->energi>enerjiSpawn+10&&move.first>=0&&move.first<=sizeX && move.second>=0 && move.second<=sizeY){
		plant->setObj(move, poin(move, genSize, genomSize, enerjiSpawn, brain(genSize, genomSize, point->Brain.dell(z))));
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
			if(plant->getObj(move)!=nullptr){
			for (int a=0; a<plant->box.size(); a++){
				if(plant->box[a].getPos()==move){
					point->killUp();
					point->energi+=plant->box[a].energi;
					if(point->energi>maxEnerji){point->energi=maxEnerji-1;};
					killPoint(plant, &plant->box[a], del);
					plant->update();
					return;
				};
			};
			};
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
		default:
			return;
	};
	};
};


int main() {
    map plant = map(sizeX, sizeY);
    plant.setObj({2, 2}, poin({2, 2}, 3, 3, 3));
    plant.setObj({3, 2}, poin({3, 2}, 3, 3, 3));
    plant.printPlant();
    int u=1;
    delPoin(&plant, &plant.box[u], &u);
    plant.update();
    cout<<"\n";
    plant.printPlant();
}