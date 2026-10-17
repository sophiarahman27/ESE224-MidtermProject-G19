// Fleet.cpp
// ESE 224 Fall 2026 Midterm Project (starter code)
// Team members: Sophia and Nafisa
//
// Every function below compiles but does nothing useful yet.
// Replace each TODO with your implementation (see Section 4 of the handout).
// Remember: no <algorithm>, no std::sort, std::swap, std::find, or std::shuffle.

#include "Fleet.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// ---------- Private helpers ----------

// Provided random number generator. Copy exactly; do not change.
unsigned long long Fleet::nextRandom(unsigned long long &state) const
{
    state = (state * 1103515245ULL + 12345ULL) % 2147483648ULL;
    return state;
}

void Fleet::swapDrones(int i, int j)
{
    if (i == j) return;          //check for if drones are alr the same
    Drone temp = drones[i];      //copy drone i, overwrite with j, put copy into j
    drones[i] = drones[j];       
    drones[j] = temp;            
}

bool Fleet::validIndex(int index) const
{
    if (index >= 0 && index < getSize()){
        return true;                        //compare against 0 and accessor
    }
    return false;
}

// ---------- Accessors and mutators ----------

bool Fleet::addDrone(const Drone& d)
{
    int n = getSize();
    for (int i = 0; i < n; i++){
        if (drones[i] == d){ //check for same ID
            cout << "Drone with ID " << d.getID() << " already exists in the fleet." << endl;
            return false;
        } 
    }
    drones.push_back(d);
    return true;
}

Drone Fleet::getDrone(int index) const
{
    if (index < 0 || index >= getSize()){
        cerr << "Error: drone index " << index << " is out of range" << endl;
        return Drone(); //return default uppon error
    }
    return drones[index]; //return correct drone if no error
}

int Fleet::getSize() const
{
    return (int)drones.size();
}

// ---------- Sorting ----------
// Follow the counting rules in Section 4.2 exactly; your counts are checked.

void Fleet::selectionSortByID()
{
    // TODO: ascending by ID. Print: Selection sort by ID: C comparisons, S swaps.
    int n = getSize();
    int comparisons = 0; //counts
    int swaps = 0;

    for (int i = 0; i < n -1; i++){
        int minI = i;
        for (int j = i + 1; j < n; j++){    //nested loop to compare each drone against tracked minimum index, updating when a new min is found
            comparisons++;
            if (drones[j].getID() < drones[minI].getID()){
                minI = j;
            }
        }
        if (minI != i){
            swapDrones(i, minI); //swapping if finding new minimum
            swaps++;
        }
    }

    cout << "Selection sort by ID: " << comparisons << " comparisons, " << swaps << " swaps." << endl;
}

void Fleet::insertionSortByBattery()
{
    // TODO: descending by battery. Print: Insertion sort by battery: C comparisons, H shifts.
    int n = getSize();
    int comparisons = 0;
    int shifts = 0;

    for (int i = 1; i < n; i++)
    {
        Drone key = drones[i];
        int j = i - 1;
        while (j >= 0){                                       //do not coutn start as a comparison
            comparisons++;                                   //key vs. drone at index j
            if (drones[j].getBattery() < key.getBattery()){   //lower battery moves right 
                drones[j + 1] = drones[j];
                shifts++;
                j--;
            }
            else{
                break;
            }
        }
        drones[j + 1] = key;                                 //do not count placement of key as a shift
    }

    cout << "Insertion sort by battery: " << comparisons << " comparisons, " << shifts << " shifts." << endl;

}

void Fleet::sortByName()
{
    int n = getSize();
    int comparisons = 0;
    int shifts = 0;

    for (int i = 1; i < n; i++){
        Drone key = drones[i];
        int j = i - 1;  //do not count start as a comparison/count
        while (j >= 0){
            comparisons++;
            if (drones[j].getName() > key.getName()){ //greater moves right
                drones[j + 1] = drones[j];
                shifts++;
                j--;
            }
            else{
                break;
            }
        }
        drones[j + 1] = key;
    }

    cout << "Insertion sort by name: " << comparisons << " comparisons, " << shifts << " shifts." << endl;
}

bool Fleet::isSortedByID() const
{
    for (int i = 1; i < getSize(); i++){
            if (drones[i - 1].getID() > drones[i].getID()){
                return false; //if any drone is greater than the next, return false
            }
        return true;                                             // empty or one drone counts as sorted
    }
    return false;
}

// ---------- Searching ----------

int Fleet::linearSearchByName(const string& name) const
{
    // TODO: one comparison per drone checked; print the count; return index or -1
    return -1;
}

int Fleet::binarySearchByID(int id)
{
    // TODO: sort first if needed (print a message), then binary search.
    // One comparison per loop iteration. Print the count; return index or -1.
    return -1;
}

// ---------- Dispatching ----------

int Fleet::findNearestAvailable(int x, int y, double weight) const
{
    // TODO: closest drone that canDeliver; ties go to the smaller ID; -1 if none
    return -1;
}

bool Fleet::dispatchDrone(int index, int x, int y, double weight)
{
    // TODO: check index and canDeliver, then completeDelivery
    return false;
}

bool Fleet::rechargeDrone(int id)
{
    // TODO: battery 100 and IDLE, unless MAINTENANCE; message if not found
    return false;
}

void Fleet::countByStatus() const
{
    // TODO: counts of IDLE, CHARGING, MAINTENANCE and the average battery
}

void Fleet::processOrders(const string& orderFile, const string& logFile)
{
    // TODO: for each order in file order, find the nearest available drone and dispatch it.
    // Write one line per order to the screen and the log, then the summary line.
    // Sum the exact distances; round only when printing.
}

// ---------- Other ----------

void Fleet::shuffleFleet(unsigned long long seed)
{
    // TODO: Fisher-Yates. state = seed; for i from n-1 down to 1:
    //       j = nextRandom(state) % (i + 1), then swap drones i and j.
}

void Fleet::displayAll() const
{
    // TODO: print every drone with its index
}

void Fleet::displayDrone(int index) const
{
    // TODO: check the range, then print one drone
}

void Fleet::writeFleetToFile(const string& filename) const
{
    // TODO: same format as drones.txt plus deliveriesCompleted; one decimal for battery and payload
}
