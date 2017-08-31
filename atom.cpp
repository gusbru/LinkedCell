//
// Created by gusbru on 30/08/17.
//
#include <iostream>
#include "atom.h"

using namespace std;

// Constructor
atom::atom(int id, double x, double y, double z) {
    this->id = id;
    this->x = x;
    this->y = y;
    this->z = z;
    this->neighbor = nullptr;
}


double atom::getX() {
    return this->x;
}

double atom::getY() {
    return this->y;
}

double atom::getZ() {
    return this->z;
}

atom *atom::getNeighbor() {
    return this->neighbor;
}

int atom::getId() {
    return this->id;
}

void atom::setX(double x) {
    this->x = x;
}

void atom::setY(double y) {
    this->y = y;
}

void atom::setZ(double z) {
    this->z = z;
}

void atom::setNeighbor(atom *neighbor) {
    this->neighbor = neighbor;
}
