//
// Created by gusbru on 30/08/17.
//
#include <iostream>
#include "linkedcell.h"
#include "atom.h"

using namespace std;

// Constructor
linkedcell::linkedcell(int cellId, atom* neighbor) {
    this->cellId = cellId;
    this->neighbor = neighbor;
}

int linkedcell::getCellId() {
    return this->cellId;
}

atom *linkedcell::getNeighbor() {
    return this->neighbor;
}

void linkedcell::setCellId(int cellId) {
    this->cellId = cellId;
}

void linkedcell::setNeighbor(atom * neighbor) {
    this->neighbor = neighbor;
}



//void addLinkedCell(int cellIndex, atom *atomIndex, lcHead **head) {
//
//    // first cell
//    if ((*head) == nullptr) {
//        (*head) = new(lcHead);
//        (*head)->cellId = cellIndex;
//        (*head)->neighbor = atomIndex;
//        (*head)->next = nullptr;
//        return;
//    }
//
//    lcHead *current = (*head);
//
//    while(current->next != nullptr){
//        current = current->next;
//    }
//
//    current->next = new(lcHead);
//    current = current->next;
//    current->cellId = cellIndex;
//    current->neighbor = atomIndex;
//    current->next = nullptr;
//}
//
//void printLinkedCell(lcHead *head) {
//    lcHead *current = head;
//    string atomIndex;
//    while (current != nullptr) {
//        if(current->neighbor != nullptr) {
//            atom *atom = current->neighbor;
//            string list = "";
//            while(atom != nullptr) {
//                list.append("-->");
//                list.append(to_string(atom->id));
//                atom = atom->neighbor;
//            }
//            atomIndex = list;
//        } else {
//            atomIndex = "EMPTY";
//        }
//        cout << "Cell  = " << current->cellId << " with first atom id = " << atomIndex << endl;
//        current = current->next;
//    }
//}