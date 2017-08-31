//
// Created by gusbru on 30/08/17.
//
#include "atom.h"
#ifndef LINKEDCELL_LINKEDCELL_H
#define LINKEDCELL_LINKEDCELL_H


class linkedcell {
public:
    linkedcell(int, atom*);
    int getCellId();
    atom* getNeighbor();
    void setCellId(int);
    void setNeighbor(atom*);

private:
    int cellId;
    struct atom *neighbor;
};


#endif //LINKEDCELL_LINKEDCELL_H
