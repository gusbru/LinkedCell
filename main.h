//
// Created by gusbru on 28/08/17.
//

#ifndef LINKEDCELL_MAIN_H
#define LINKEDCELL_MAIN_H
#include <array>

//Atoms
typedef struct atom;
typedef struct lcHead;

//Box size;
std::array<double,3> boxLength; /* box size in the x|y|z directions */
std::array<double,3> rc;        /* Length of a cell in the x|y|z direction */
std::array<int,3> Lc;           /* Number of cells in the x|y|z direction */

// Parameters
double RCUT = 2.5;
double SKIN = 0.5;

//
int nAtoms;
int mc[3];                      /* vector cell index */
int c;                          /* serial cell index */

// constants
#define EMPTY (-1)

// functions and prototypes
void addAtom(double x, double y, double z, atom *head);
int numberOfAtoms(atom *head);
void printAtoms(atom *head);
#endif //LINKEDCELL_MAIN_H
