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
            ++comparisons;
            if (drones[j].getID() < drones[minI].getID()){
                minI = j;
            }
        }
        if (minI != i){
            swapDrones(i, minI); //swapping if finding new minimum
            ++swaps;
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

    for (int i = 1; i < n; i++){
        Drone key = drones[i];
        int j = i - 1;
        while (j >= 0){                                       //do not count start as a comparison
            ++comparisons;                                   //key vs. drone at index j
            if (drones[j].getBattery() < key.getBattery()){   //lower battery moves right 
                drones[j + 1] = drones[j];
                ++shifts;
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
            ++comparisons;
            if (drones[j].getName() > key.getName()){ //greater moves right
                drones[j + 1] = drones[j];
                ++shifts;
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
            return false;               //if pair out of order found, return false
        }
    }
    return true;                        //checked or only 0/1 drones
}

// ---------- Searching ----------

int Fleet::linearSearchByName(const string& name) const
{
    // TODO: one comparison per drone checked; print the count; return index or -1
    int n = getSize();
    int comparisons = 0;

    for (int i = 0; i < n; i++){
        ++comparisons;
        if(drones[i].getName() == name){ 
            cout << "Linear search comparisons: " << comparisons << endl;
            return i;   //i s the index of the drone with the matching name
        }
    }
    cout << "Linear search comparisons: " << comparisons << endl;
    return -1;
}

int Fleet::binarySearchByID(int id)
{
    if (!isSortedByID()){
        cout << "Fleet is not sorted by ID. Sorting now. . ." << endl;
        selectionSortByID();
    }

    int count = 0;
    int low = 0;
    int high = getSize() - 1;

    while (low <= high){
        int mid = (low + high) / 2;
        int midID = drones[mid].getID();
        ++count;                        //one comparison for every middle element examined

        //standard binary search algorithm
        if (midID == id){
            cout << "Binary Search Comparisons: " << count << endl;
            return mid;
        }else if (midID < id){
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }
    cout << "Binary Search Comparisons: " << count << endl;
    return -1;
}

// ---------- Dispatching ----------

int Fleet::findNearestAvailable(int x, int y, double weight) const
{
    // TODO: closest drone that canDeliver; ties go to the smaller ID; -1 if none
    int n = getSize();
    int bestIndex = -1; //will change to first index of loop
    int bestDist = 0; //change based on first drone that can deliver based on distacnce

    for(int i = 0; i < n; i++){
        if(!drones[i].canDeliver(x, y, weight)){  //check weight restrictions
            continue;
        }

        int dx = drones[i].getPosition(0) - x; //comparing coordinates
        int dy = drones[i].getPosition(1) - y;
        int dist = dx * dx + dy * dy;

        //this long header decides which drone is best by comparing values
        if(bestIndex == -1 || dist < bestDist || (dist == bestDist && drones[i].getID() < drones[bestIndex].getID())){
            bestIndex = i;
            bestDist = dist;
        }
    }
    return bestIndex;
}

bool Fleet::dispatchDrone(int index, int x, int y, double weight)
{
    // TODO: check index and canDeliver, then completeDelivery
    if(index < 0 || index > getSize()){
        return false;
    }

    if(!drones[index].canDeliver(x, y, weight)){
        return false;
    }

    drones[index].completeDelivery(x, y, weight);
    return true;
}

bool Fleet::rechargeDrone(int id)
{
    // TODO: battery 100 and IDLE, unless MAINTENANCE; message if not found
    for(int i = 0; i < getSize(); i++){
        if(drones[i].getID() == id){
            drones[i].setBattery(100); //recharge battery of chosen drone

            if(drones[i].getStatus() != "MAINTENANCE"){
                drones[i].setStatus("IDLE");
            }
            return true;
        }
    }
    cout << "Drone with ID: " << id << " not found." << endl;
    return false;
}

void Fleet::countByStatus() const
{
    // TODO: counts of IDLE, CHARGING, MAINTENANCE and the average battery
    int countIDLE = 0;
    int countCHARGING = 0;
    int countMAINTENANCE = 0;
    double avgBattery = 0.0;
    double sum = 0.0;

    //simply count each status and sum battery levels, then calculate average
    for(int i = 0; i < getSize(); i++){
        if(drones[i].getStatus() == "IDLE"){ 
            ++countIDLE;
        }else if(drones[i].getStatus() == "CHARGING"){
            ++countCHARGING;
        }else if(drones[i].getStatus() == "MAINTENANCE"){
            ++countMAINTENANCE;
        }

        sum += drones[i].getBattery(); 
    }

    avgBattery = sum / getSize(); 

    cout << "Total IDLE drones: " << countIDLE << endl;
    cout << "Total CHARGING drones: " << countCHARGING << endl;
    cout << "Total MAINTENANCE drones: " << countMAINTENANCE << endl;
    cout << "Average Battery: " << fixed << setprecision(1) << avgBattery << "%" << endl;
}

void Fleet::processOrders(const string& orderFile, const string& logFile)
{
    // TODO: for each order in file order, find the nearest available drone and dispatch it.
    // Write one line per order to the screen and the log, then the summary line.
    // Sum the exact distances; round only when printing.
    ifstream in(orderFile);
    ofstream log(logFile);

    if (!in) {
        cout << "Could not open order file: " << orderFile << endl;
        return;
    }
    if (!log) {
        cout << "Could not open log file: " << logFile << endl;
        return;
    }

    int orderID, x, y;
    double weight;
    int totalOrders = 0;
    int assigned = 0;
    double totalDistance = 0.0;

    while(in >> orderID >> x >> y >> weight){
        ++totalOrders;
        int index = findNearestAvailable(x, y, weight);

        if(index == -1){
            cout << "Order " << orderID << ": Unassigned" << endl;
            log << "Order " << orderID << ": Unassigned" << endl;
        }else{
            int droneID = drones[index].getID();
            string droneName = drones[index].getName();
            double dist = drones[index].distanceTo(x, y);
            double batteryBefore = drones[index].getBattery();

            dispatchDrone(index, x, y, weight);

            double batteryAfter = drones[index].getBattery();
            totalDistance += dist;
            ++assigned;

             cout << "Order " << orderID << ": Drone " << droneID
             << " (" << droneName << ") distance " << dist
             << " battery " << batteryBefore << " -> " << batteryAfter << endl;
        log  << "Order " << orderID << ": Drone " << droneID
             << " (" << droneName << ") distance " << dist
             << " battery " << batteryBefore << " -> " << batteryAfter << endl;
        }
    }

    cout << "Assigned " << assigned << " of " << totalOrders
         << " orders. Total distance flown: " << totalDistance << endl;
    log  << "Assigned " << assigned << " of " << totalOrders
         << " orders. Total distance flown: " << totalDistance << endl;

}

// ---------- Other ----------

void Fleet::shuffleFleet(unsigned long long seed)
{
    // TODO: Fisher-Yates. state = seed; for i from n-1 down to 1:
    //       j = nextRandom(state) % (i + 1), then swap drones i and j.
    unsigned long long state = seed;
    int n = getSize();
    for(int i = n - 1; i >= 1; i--){
        int j = nextRandom(state) % (i + 1);

        Drone temp = drones[i];
        drones[i] = drones[j];
        drones[j] = temp;
    }

}

void Fleet::displayAll() const
{
    // TODO: print every drone with its index
    for(int i = 0; i < getSize(); i++){
        cout << "Drone [" << i << "]" << endl;
        drones[i].displayDrone();
        cout << endl;
    }
}

void Fleet::displayDrone(int index) const
{
    // TODO: check the range, then print one drone
    if(index < 0 || index > getSize()){
        cout << "Error: invalid drone index " << index << endl;
        return;
    }
    drones[index].displayDrone();
}

void Fleet::writeFleetToFile(const string& filename) const
{
    // TODO: same format as drones.txt plus deliveriesCompleted; one decimal for battery and payload
    ofstream out(filename);

    if (!out) {
        cout << "Error: could not open file " << filename << endl;
        return;
    }

    out << fixed << setprecision(1);

    for (int i = 0; i < getSize(); ++i) {
        out << drones[i].getName() << " "
            << drones[i].getID() << " "
            << drones[i].getModel() << " "
            << drones[i].getBattery() << " "
            << drones[i].getMaxPayload() << " "
            << drones[i].getPosition(0) << " "
            << drones[i].getPosition(1) << " "
            << drones[i].getStatus() << " "
            << drones[i].getDeliveriesCompleted() << endl;
    }
}
