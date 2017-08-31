//
// Created by gusbru on 30/08/17.
//
#include <vector>
#ifndef LINKEDCELL_ATOM_H
#define LINKEDCELL_ATOM_H


class atom {
public:
    atom(int, double, double, double);
    int getId();
    double getX();
    double getY();
    double getZ();
    atom *getNeighbor();

    void setX(double);
    void setY(double);
    void setZ(double);
    void setNeighbor(atom*);


private:
    int id;
    double x;
    double y;
    double z;
    atom *neighbor;

};



#endif //LINKEDCELL_ATOM_H
