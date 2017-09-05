#include <iostream>
#include <vector>
#include "main.h"
#include "atom.h"
#include "linkedcell.h"

using namespace std;


void print(vector<atom> &vector) {
    for (int i = 0; i < vector.size(); ++i) {
        cout << "AtomNumber(" << i << ")\t|x=" << vector[i].getX() << "\t|y=" << vector[i].getY() << "\t|z="
             << vector[i].getZ() << endl;
    }
}

void printLinkedCell(vector<linkedcell> &head) {
    string atomIndex;
    for (int k = 0; k < head.size(); ++k) { // for each cell
        if (head[k].getNeighbor() != nullptr) {
            atom *atom = head[k].getNeighbor();
            string list;
            while (atom != nullptr) {
                list.append("-->");
                list.append(to_string(atom->getId()));
                atom = atom->getNeighbor();
            }
            atomIndex = list;
        } else {
            atomIndex = "EMPTY";
        }
        cout << "Cell  = " << k << " with atoms = " << atomIndex << endl;
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

    vector<atom> myAtoms;
    myAtoms.emplace_back(atom(0, 1.0, 1.0, 0.0));
    myAtoms.emplace_back(atom(1, 6.0, 0.5, 0.0));
    myAtoms.emplace_back(atom(2, 5.5, 1.5, 0.0));
    myAtoms.emplace_back(atom(3, 6.5, 2.5, 0.0));
    myAtoms.emplace_back(atom(4, 3.0, 5.5, 0.0));
    myAtoms.emplace_back(atom(5, 4.0, 3.5, 0.0));
    myAtoms.emplace_back(atom(6, 6.0, 5.0, 0.0));
    myAtoms.emplace_back(atom(7, 8.5, 5.5, 0.0));
    myAtoms.emplace_back(atom(8, 6.5, 7.0, 0.0));
    myAtoms.emplace_back(atom(9, 1.5, 10.0, 0.0));

    // Count the number of atoms
    nAtoms = myAtoms.size();

    cout << "Box with " << nAtoms << " atoms" << endl;
    print(myAtoms);



    // Divide the simulation box into small cells
    cout << "Size of each cell" << endl;
    for (int alpha = 0; alpha < boxLength.size(); alpha++) {
        Lc[alpha] = (int) (boxLength[alpha] / RCUT);
        rc[alpha] = boxLength[alpha] / Lc[alpha];

        cout << "Lc[" << alpha << "] = " << Lc[alpha] << " (rc[" << alpha << "] = " << rc[alpha] << ")" << endl;

    }

    // making the linked-cell list
    int lcyz;
    int lcxyz;

    lcyz = Lc[1] * Lc[2];
    lcxyz = Lc[0] * lcyz;

    cout << "lcyz =  " << lcyz << endl;
    cout << "lcxyz (number of cells) = " << lcxyz << endl; // number of cells

    /* Reset the headers (loop over the cells) */
    vector<linkedcell> head;
    for (int i = 0; i < lcxyz; i++) {
        head.emplace_back(i, nullptr);
    }


    /* Scan atoms to construct headers, head and linked lists, lscl */
    for (int j = 0; j < nAtoms; ++j) {

        double r[3] = {myAtoms[j].getX(), myAtoms[j].getY(), myAtoms[j].getZ()};
        for (int a = 0; a < 3; a++) {
            mc[a] = (int) (r[a] / rc[a]);
        }

        /* Translate the vector cell index (mc) to a scalar index */
        c = mc[0] * lcyz + mc[1] * Lc[2] + mc[2];

        /* Link the previous occupant (EMPTY if 1st on the list) */
        myAtoms[j].setNeighbor(head[c].getNeighbor());
        //cout << "atom " << myAtoms[j].getId() << " is at cell " << head[c].getCellId() << " with neighbor " << endl;

        /* The last one goes to the header */
        head[c].setNeighbor(&myAtoms[j]);

    }

    printLinkedCell(head);


    /* calculate the pair interaction */

    // probe atom
    atom probeAtom = atom(99, 9, 2.5, 2.5);

    for (mc[0] = 0; mc[0] < Lc[0]; (mc[0])++) {
        for (mc[1] = 0; mc[1] < Lc[1]; (mc[1])++) {
            for (mc[2] = 0; mc[2] < Lc[2]; (mc[2])++) {

                // calculate the scalar cell index
                c = mc[0] * lcyz + mc[1] * Lc[2] + mc[2];

                cout << "cell (x,y,z,index)" << mc[0] << " " << mc[1] << " " << mc[2] << " " << c << endl;

                int neighborNumber = 0;

                if (head[c].getNeighbor() != nullptr) { // if the cell is not empty
                    for (mc1[0] = mc[0] - 1; mc1[0] <= mc[0] + 1; (mc1[0])++) {
                        for (mc1[1] = mc[1] - 1; mc1[1] <= mc[1] + 1; (mc1[1])++) {
                            for (mc1[2] = mc[2] - 1; mc1[2] <= mc[2] + 1; (mc1[2])++) {

                                if (mc1[0] >= 0 && mc1[1] >= 0 && mc1[2] >= 0 &&
                                    mc1[0] < Lc[0] && mc1[1] < Lc[1] && mc1[2] < Lc[2]) { // non-periodic box


                                    c1 = ((mc1[0] + Lc[0]) % Lc[0]) * lcyz
                                         + ((mc1[1] + Lc[1]) % Lc[1]) * Lc[2]
                                         + ((mc1[2] + Lc[2]) % Lc[2]);


                                    neighborNumber += 1;
                                    cout << "\t\t\t(" << neighborNumber << ") has neighbor (x,y,z,index) " << mc1[0]
                                         << " " << mc1[1] << " " << mc1[2] << " " << c1 << endl;
                                }

                            }
                        }
                    }
                }


            }
        }
    }

    return 0;
}