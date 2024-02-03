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
                a = plant->box.erase((a));
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
            
            default:
            return;
        };
    };
};

int main(int argc, char *argv[])
{
    map plant = map(sizeX, sizeY);
    startGetPoin(&plant);
    int delI = 0;
    for (int c=0; c<100000; c++){
        for(int i=plant.box.size()-1; i>=0; i--){
            if(i==0){
                for(auto a=plant.box.begin(); a!=plant.box.end(); a++){
                    a->old++;
                };
                for (auto it = plant.box.begin(); it != plant.box.end(); ) {
    if (it->old > maxOld) {
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
            };
            runBrain(&plant, &plant.box[i], &i);
            if(i%1==0){
                cout<<"\n";
                plant.printPlant();
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            };
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