#ifndef BRAIN_H
#define BRAIN_H
#include <vector>
#include <iostream>

class brain{
    public:
    brain(int, int);
    brain(int, int, std::vector<int>);
    int run();
    std::vector<int> dell(int);
    void drawBr();
    void moveGenSet(int);
		
	
    private:
    int sizeGen;
    std::vector<int> genom;
    int genomSize;
    int genSet;
};

#endif