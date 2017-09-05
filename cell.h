//
// Created by gusbru on 05/09/17.
//
#include <vector>
#include "linkedcell.h"

#ifndef LINKEDCELL_CELL_H
#define LINKEDCELL_CELL_H

using namespace std;

class cell {
public:
    cell(int, int, int, int);
    int getCx();
    int getCy();
    int getCz();
    int getCid();
    unsigned long getNumNeighbor();
    vector<linkedcell*> getListNeighbor();
    void setCx(int);
    void setCy(int);
    void setCz(int);
    void setCid(int);
    void addNeighbor(linkedcell*);

private:
    int cX;
    int cY;
    int cZ;
    int c;
    vector<linkedcell*> cellNeighbors;

};


#endif //LINKEDCELL_CELL_H
