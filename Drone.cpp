// Drone.cpp
// ESE 224 Fall 2026 Midterm Project (starter code)
// Team members: Sophia Rahman and Nafisa Patwary
//
// Every function below compiles but does nothing useful yet.
// Replace each TODO with your implementation (see Section 3 of the handout).

#include "Drone.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

// ---------- Constructors ----------

Drone::Drone()
{
    // TODO: set every member to its default value (table in Section 3.2)
    name = ""; // SOP
    ID = -1;
    model = ""; // SOP
    battery = 100.0;
    maxPayload = 0.0;
    position[0] = 0;
    position[1] = 0;
    status = "IDLE";
    deliveriesCompleted = 0;
}

Drone::Drone(const string& n, int id, const string& m, double b, double p,
             int x, int y, const string& s) : Drone()
{
    // TODO: set each member by calling its mutator, so invalid values keep the default
    setName(n); // Line 34 - 41 by SOP
    setID(id);
    setModel(m);
    setBattery(b);
    setMaxPayload(p);
    setPosition(0, x);
    setPosition(1, y);
    setStatus(s);
}

// ---------- Accessors ----------

string Drone::getName() const { return name; }
int Drone::getID() const { return ID; }
string Drone::getModel() const { return model; }
double Drone::getBattery() const { return battery; }
double Drone::getMaxPayload() const { return maxPayload; }
string Drone::getStatus() const { return status; }
int Drone::getDeliveriesCompleted() const { return deliveriesCompleted; }

int Drone::getPosition(int index) const
{
    // TODO: index 0 is x, index 1 is y; any other index prints an error and returns -1
    if(index == 0){        // Line 57 - 64 by SOP
        return position[0];
    }else if(index == 1){
        return position[1];
    }else{
        cout << "Error: position index must be a 0 or a 1" << endl;
        return -1;
    }
}

// ---------- Mutators ----------

void Drone::setName(const string& n)
{
    name = n;
}

bool Drone::setID(int id)
{
    // TODO: valid when id > 0
    if(id > 0){      // Line 77 - 81 by SOP
        ID = id;
        return true;
    }
    cout << "Error: ID must be greater than 0" << endl;
    return false;
}

bool Drone::setModel(const string& m)
{
    // TODO: valid when m is "Kestrel", "Falcon", or "Condor"
    if(m == "Kestrel" || m == "Falcon" || m == "Condor"){  // Line 88 - 92 by SOP
        model = m;
        return true;
    }
    cout << "Error: model must be Kestrel or Falcon or Condor" << endl;
    return false;
}

bool Drone::setBattery(double b)
{
    // TODO: valid when 0 <= b <= 100
    if(b >= 0 && b <= 100){  // Line 99 - 103 by SOP
        battery = b;
        return true;
    }
    cout << "Error: battery value must be between 0 and 100" << endl;
    return false;
}

bool Drone::setMaxPayload(double p)
{
    // TODO: valid when p > 0
    if(p > 0){
        maxPayload = p;
        return true;
    }
    cout << "Error: the max payload must be greater than 0" << endl;
    return false;
}

bool Drone::setPosition(int index, int value)
{
    // TODO: valid when index is 0 or 1 and value >= 0
    if((index == 0 || index == 1) && value >= 0){ // Line 121 - 125 by SOP
        position[index] = value;
        return true;
    }
    cout << "Error: position index must be 0 or 1 and value must be greater than or equal to 0" << endl;
    return false;
}

bool Drone::setStatus(const string& s)
{
    // TODO: valid when s is "IDLE", "CHARGING", or "MAINTENANCE"
    if(s == "IDLE" || s == "CHARGING" || s == "MAINTENANCE"){
        status = s;
        return true;
    }
    cout << "Error: status must be IDLE or CHARGING or MAINTENANCE" << endl;
    return false;
}

// ---------- Delivery methods ----------

double Drone::distanceTo(int x, int y) const
{
    // TODO: straight-line distance from this drone to (x, y)
    return 0.0;
}

double Drone::batteryNeeded(int x, int y, double weight) const
{
    // TODO: distanceTo(x, y) * BATTERY_PER_UNIT * (1 + PAYLOAD_FACTOR * weight)
    return 0.0;
}

bool Drone::canDeliver(int x, int y, double weight) const
{
    // TODO: IDLE, weight <= maxPayload, and enough battery to keep SAFETY_RESERVE
    return false;
}

void Drone::completeDelivery(int x, int y, double weight)
{
    // TODO: use battery, move to (x, y), count the delivery, switch to CHARGING if below LOW_BATTERY
}

// ---------- Display and comparison ----------

void Drone::displayDrone() const
{
    // TODO: print every member with a label
}

bool Drone::operator==(const Drone& other) const
{
    // TODO: two drones are equal if they have the same ID
    return false;
}
