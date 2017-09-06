#include <iostream>
#include <vector>
#include "main.h"
#include "atom.h"
#include "linkedcell.h"
#include "cell.h"
#include <cmath>
#include <fstream>

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

/**************************************************************
 *
 * Calculate the vector cell index from the
 *
 * @param x position x
 * @param y position y
 * @param z position z
 * @return the vector cell index
 **************************************************************/
int calcCellIndex(double x, double y, double z) {
    double r[3] = {x, y, z};

    for (int a = 0; a < 3; a++) {
        mc[a] = (int) (r[a] / rc[a]);
    }

    /* Translate the vector cell index (mc) to a scalar index */
    c = mc[0] * Lc[1]*Lc[2] + mc[1] * Lc[2] + mc[2];

    return c;
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

    nAtoms = 10;
    atom** myAtoms2;
    myAtoms2 = new atom*[10];

    ifstream inpFileAtoms("../coordinates.xyz");
    string line;
    double x, y, z;
    if (inpFileAtoms.is_open()){
        getline(inpFileAtoms, line);
        long n = stol(line);
        cout << n << endl;

        getline(inpFileAtoms, line);

        for (int i = 0; i < n; ++i) {
            getline(inpFileAtoms, line);
            cout << line << endl;
        }

    } else {
        cout << "Unable to open file" << endl;
        return 0;
    }

    myAtoms2[0] = new atom(0, 1.0, 1.0, 0.0);
    myAtoms2[1] = new atom(1, 6.0, 0.5, 0.0);
    myAtoms2[2] = new atom(2, 5.5, 1.5, 0.0);
    myAtoms2[3] = new atom(3, 6.5, 2.5, 0.0);
    myAtoms2[4] = new atom(4, 3.0, 5.5, 0.0);
    myAtoms2[5] = new atom(5, 4.0, 3.5, 0.0);
    myAtoms2[6] = new atom(6, 6.0, 5.0, 0.0);
    myAtoms2[7] = new atom(7, 8.5, 5.5, 0.0);
    myAtoms2[8] = new atom(8, 6.5, 7.0, 0.0);
    myAtoms2[9] = new atom(9, 1.5, 10.0, 0.0);


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
    atom probeAtom = atom(99, 3.0, 7.0, 2.4);

    vector<cell> neighbors;
    //neighbors = new cell **[lcxyz];

    for (mc[0] = 0; mc[0] < Lc[0]; (mc[0])++) {
        for (mc[1] = 0; mc[1] < Lc[1]; (mc[1])++) {
            for (mc[2] = 0; mc[2] < Lc[2]; (mc[2])++) {

                // calculate the scalar cell index
                c = mc[0] * lcyz + mc[1] * Lc[2] + mc[2];



                //cout << "cell (x,y,z,index)" << mc[0] << " " << mc[1] << " " << mc[2] << " " << c << endl;


                neighbors.emplace_back(cell(mc[0], mc[1], mc[2], c));


                /************************************************************************************/
                //int neighborNumber = 0;
                //if (head[c].getNeighbor() != nullptr) { // if the cell is not empty
                    for (mc1[0] = mc[0] - 1; mc1[0] <= mc[0] + 1; (mc1[0])++) {
                        for (mc1[1] = mc[1] - 1; mc1[1] <= mc[1] + 1; (mc1[1])++) {
                            for (mc1[2] = mc[2] - 1; mc1[2] <= mc[2] + 1; (mc1[2])++) {

                                if (mc1[0] >= 0 && mc1[1] >= 0 && mc1[2] >= 0 &&
                                    mc1[0] < Lc[0] && mc1[1] < Lc[1] && mc1[2] < Lc[2]) { // non-periodic box


                                    c1 = ((mc1[0] + Lc[0]) % Lc[0]) * lcyz
                                         + ((mc1[1] + Lc[1]) % Lc[1]) * Lc[2]
                                         + ((mc1[2] + Lc[2]) % Lc[2]);


                                    neighbors[c].addNeighbor(&head[c1]);
                                    //[neighborNumber] = new cell(mc[0], mc[1], mc[2], c1);

                                    cout << "c = " << c << " " << neighbors[c].getNumNeighbor() << endl;

                                    //cout << "\t\t\t(" << neighborNumber << ") has neighbor (x,y,z,index) " << mc1[0]
                                    //     << " " << mc1[1] << " " << mc1[2] << " " << c1 << endl;
                                }
                            }
                        }
                    }
                //}
                /************************************************************************************/




            }
        }
    }


    cout << "************************************************************************************" << endl;
    cout << "*       From the coordinates of the probe atom (x,y,z) and calculate cProbe        *" << endl;
    cout << "************************************************************************************" << endl;
    int cProbe = calcCellIndex(probeAtom.getX(), probeAtom.getY(), probeAtom.getZ());

    cout << "cProbe = " << cProbe << endl;

    cout << endl;
    cout << "************************************************************************************" << endl;
    cout << "*                            Getting the neighbor cells                            *" << endl;
    cout << "************************************************************************************" << endl;
    vector<linkedcell*> listCellNeighbors = neighbors[cProbe].getListNeighbor();

    string list;
    for (int i = 0; i < listCellNeighbors.size(); i++){
        list += to_string(listCellNeighbors[i]->getCellId());
        list += "->";
    }
    cout << list << endl;


    cout << endl;
    cout << "************************************************************************************" << endl;
    cout << "*                            Getting the neighbor atoms                            *" << endl;
    cout << "************************************************************************************" << endl;
    vector<int> atomList;
    for (int i = 0; i < listCellNeighbors.size(); i++){
        int cellId = listCellNeighbors[i]->getCellId();
        atom* atom = head[cellId].getNeighbor();
        while (atom != nullptr) {
            atomList.emplace_back(atom->getId());
            atom = atom->getNeighbor();
        }
    }

    cout << "The atoms are: ";
    for (int k = 0; k < atomList.size(); ++k) {
        cout << atomList[k] << " ";
    }
    cout << endl;

    cout << endl;
    cout << "************************************************************************************" << endl;
    cout << "*                            Calculate the Potential                               *" << endl;
    cout << "************************************************************************************" << endl;
    double Upot = 0.0;
    double epsilon = 1.0;
    double sigma = 1.0;
    for (int l = 0; l < atomList.size(); ++l) {
        double r = sqrt(
                pow(probeAtom.getX()-myAtoms[atomList[l]].getX(), 2.0) +
                pow(probeAtom.getY()-myAtoms[atomList[l]].getY(), 2.0) +
                pow(probeAtom.getY()-myAtoms[atomList[l]].getY(), 2.0)
        );
        if (r <= RCUT) {
            Upot += 4.0 * ( pow((sigma/r),12.0) - pow((sigma/r),6.0) );
        }

    }

    cout << "Upot = " << Upot << endl;
    

return 0;
}