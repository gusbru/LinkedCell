//
// Created by gusbru on 05/09/17.
//
#include <vector>
#include "cell.h"
#include "linkedcell.h"

using namespace std;

cell::cell(int cX, int cY, int cZ, int c) {
    this->cX = cX;
    this->cY = cY;
    this->cZ = cZ;
    this->c = c;
}

int cell::getCx() {
    return this->cX;
}

int cell::getCy() {
    return this->cY;
}

int cell::getCz() {
    return this->cZ;
}

int cell::getCid() {
    return this->c;
}

void cell::setCx(int cX) {
    this->cX = cX;
}

void cell::setCy(int cY) {
    this->cY = cY;
}

void cell::setCz(int cZ) {
    this->cZ = cZ;
}

void cell::setCid(int c) {
    this->c = c;
}

void cell::addNeighbor(linkedcell* cell) {
    cellNeighbors.emplace_back(cell);
}

unsigned long cell::getNumNeighbor() {
    return cellNeighbors.size();
}

vector<linkedcell*> cell::getListNeighbor() {
    vector<linkedcell*> list;
    for(int i = 0; i < cellNeighbors.size(); ++i) {
        list.emplace_back(cellNeighbors[i]);
    }
    return list;
}


