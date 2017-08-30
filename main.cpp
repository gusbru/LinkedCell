#include <iostream>
#include "main.h"

using namespace std;

typedef struct atom {
    int id;
    double x;
    double y;
    double z;
    struct atom *neighbor;
    struct atom *next;
};



typedef struct lcHead {
    int cellId;
    struct atom *neighbor;
    struct lcHead *next;
};

void addAtom(double x, double y, double z, atom **head){

    // first atom added
    if ((*head) == nullptr) {
        (*head) = new(atom);
        (*head)->id = 0;
        (*head)->x = x;
        (*head)->y = y;
        (*head)->z = z;
        (*head)->next = nullptr;
        return;
    }

    atom *current = (*head);

    // go to the last atom
    while (current->next != nullptr){
        current = current->next;
    }

    //include the new atom in the end
    current->next = new(atom);
    int id = current->id + 1;
    current = current->next;
    current->id = id;
    current->x = x;
    current->y = y;
    current->z = z;
    current->next = nullptr;

}

int numberOfAtoms(atom *head){
    int count = 0;
    atom *current = head;

    while(current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

void printAtoms(atom *head) {
    atom *current = head;

    while(current != nullptr) {
        cout << "AtomNumber(" << current->id << ")\t|x=" << current->x << "\t|y=" << current->y << "\t|z=" << current->z << endl;
        current = current->next;
    }
}

void addLinkedCell(int cellIndex, atom *atomIndex, lcHead **head) {

    // first cell
    if ((*head) == nullptr) {
        (*head) = new(lcHead);
        (*head)->cellId = cellIndex;
        (*head)->neighbor = atomIndex;
        (*head)->next = nullptr;
        return;
    }

    lcHead *current = (*head);

    while(current->next != nullptr){
        current = current->next;
    }

    current->next = new(lcHead);
    current = current->next;
    current->cellId = cellIndex;
    current->neighbor = atomIndex;
    current->next = nullptr;
}

void printLinkedCell(lcHead *head) {
    lcHead *current = head;
    string atomIndex;
    while (current != nullptr) {
        if(current->neighbor != nullptr) {
            atom *atom = current->neighbor;
            string list = "";
            while(atom != nullptr) {
                list.append("-->");
                list.append(to_string(atom->id));
                atom = atom->neighbor;
            }
            atomIndex = list;
        } else {
            atomIndex = "EMPTY";
        }
        cout << "Cell  = " << current->cellId << " with first atom id = " << atomIndex << endl;
        current = current->next;
    }
}


int main() {

    /*******************************
     *
     * 3D box with 10 atoms
     *
     *******************************/


    // from input file
    boxLength[0] = 10.0;
    boxLength[1] = 12.0;
    boxLength[2] = RCUT;

    //
    atom *myAtoms = nullptr;

    // include 10 atoms
    addAtom(1.0, 1.0, 0.0, &myAtoms);
    addAtom(6.0, 0.5, 0.0, &myAtoms);
    addAtom(5.5, 1.5, 0.0, &myAtoms);
    addAtom(6.5, 2.5, 0.0, &myAtoms);
    addAtom(3.0, 5.5, 0.0, &myAtoms);
    addAtom(4.0, 3.5, 0.0, &myAtoms);
    addAtom(6.0, 5.0, 0.0, &myAtoms);
    addAtom(8.5, 5.5, 0.0, &myAtoms);
    addAtom(6.5, 7.0, 0.0, &myAtoms);
    addAtom(1.5, 10.0, 0.0, &myAtoms);

    // Count the number of atoms
    nAtoms = numberOfAtoms(myAtoms);

    cout << "Box with " << nAtoms << " atoms" << endl;
    printAtoms(myAtoms);


    // Divide the simulation box into small cells
    cout << "Size of each cell" << endl;
    for (int alpha = 0; alpha < boxLength.size(); alpha++) {
        Lc[alpha] = (int) (boxLength[alpha] / RCUT);
        rc[alpha] = boxLength[alpha] / Lc[alpha];

        cout << "Lc[" << alpha << "] = " << Lc[alpha] << " (rc[" << alpha << "] = " << rc[alpha] << ")" << endl;

    }

    // making the linked-cell list (lscl)
    int lcyz;
    int lcxyz;

    lcyz = Lc[1] * Lc[2];
    lcxyz = Lc[0] * lcyz;

    cout << "lcyz =  " << lcyz << endl;
    cout << "lcxyz (number of cells) = " << lcxyz << endl; // number of cells

    /* Reset the headers (loop over the cells) */
    lcHead *head = nullptr;
    for (int i = 0; i < lcxyz; i++){
        addLinkedCell(i, nullptr, &head);
    }


    /* Scan atoms to construct headers, head and linked lists, lscl */
    atom *currentAtom = myAtoms;

    while(currentAtom != nullptr){
        double r[3] = {currentAtom->x, currentAtom->y, currentAtom->z};

        for (int a = 0; a < 3; a++) {
            mc[a] = (int) (r[a] / rc[a]);
        }

        /* Translate the vector cell index (mc) to a scalar index */
        c = mc[0]*lcyz + mc[1]*Lc[2] + mc[2];

        // find the head[c] (address) first
        lcHead *currentCell = head;
        while (currentCell->cellId != c){
            currentCell = currentCell->next;
        }

        /* Link the previous occupant (EMPTY if 1st on the list) */
        currentAtom->neighbor = currentCell->neighbor;

        /* The last one goes to the header */
        currentCell->neighbor = currentAtom;


        // update the atom
        currentAtom = currentAtom->next;
    }

    printLinkedCell(head);

    // end of calculation
    free(head);
    free(myAtoms);

    return 0;
}