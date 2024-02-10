#include "brain.h"
#include <iostream>
#include <thread>

brain::brain(int genSize, int genomSize):sizeGen(genSize), genomSize(genomSize){
    for(int i=0; i<genomSize; i++){
        genom.push_back(std::rand()%sizeGen);
    }
    genSet=0;
}

brain::brain(int genSize, int genomSize, std::vector<int> gen):sizeGen(genSize), genomSize(genomSize), genom(gen){
    genSet=0;
}

int brain::run(){
    while(genSet>=genomSize){
        genSet-=genomSize;
    };
    for(int replace=0; replace<5; replace++){
        int ret=genom[genSet];
        genSet++;
        return ret;
    };
}

void brain::moveGenSet(int genJump){
    genSet+=genJump;
    while(genSet>=genomSize){
        genSet=genSet-genomSize;
    };
}

std::vector<int> brain::dell(int z){
    srand(static_cast<unsigned int>(time(0)));
    std::vector<int> ret = genom;
    for(int i = 0; i<rand()%z; i++){
        ret[rand()%genomSize]=rand()%sizeGen;
    };
    return ret;
}

void brain::drawBr(){
    for (int i=0; i<genom.size(); i++){
        std::cout<<std::to_string(genom[i]);
    };
    std::cout<<"\n";
};