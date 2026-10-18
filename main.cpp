// main.cpp
// ESE 224 Fall 2026 Midterm Project (starter code)
// Team members: TODO
//
// This skeleton compiles and shows the menu. Fill in each TODO (see Section 5 of the handout).

#include "Drone.h"
#include "Fleet.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

// TODO: ask for a username and password until the pair appears in users.txt,
//       then greet the user by name.
void login()
{
    //input file handling for logins
    ifstream usersFile("users.txt");
    if (!usersFile){
        cerr << "Error: could not open users.txt" << endl;
        exit(1);
    }

    string username;
    string pw;
    bool found = false;

    while (!found){
        cout << "Please enter your username and password, with a space in between: " << endl;
        cin >> username >> pw;

        usersFile.clear(); //clear EOF flag
        usersFile.seekg(0); //go back to the beginning of the file

        string fileUser;
        string filePw;  //read each line for pairs and compare

        while (usersFile >> fileUser >> filePw){ //checks entire pair
            if (fileUser == username && filePw == pw){
                found = true;
                break;
            }
        }

        if (!found){
            cout << "Invalid username or password. Please try again." << endl;
        }

        else{
            cout << "Welcome, " << username << "! You have succesfully logged in." << endl;
        }
    }
}

// TODO: read every drone from the file until the end of the file,
//       add each one to the fleet, and print how many were loaded.
void loadFleet(Fleet& fleet, const string& filename)
{
    ifstream dronesFile(filename);
    if (!dronesFile){
        cerr << "Error: could not open " << filename << endl;
        exit(1);
    }

    //constructor attributes
    string name;
    string model;
    string status;

    int id;
    int x;
    int y;

    double battery;
    double maxPayload;

    int count = 0;

    //read each line and create a drone object, adding it to the fleet
    while (dronesFile >> name >> id >> model >> battery >> maxPayload >> x >> y >> status){
        Drone d(name, id, model, battery, maxPayload, x, y, status);
        if (fleet.addDrone(d)){ //false if duplicate ID
            count++;
        }          
    }

    cout << "Loaded " << count << " drones." << endl;
}

void showMenu()
{
    cout << endl
         << "===== SkyDrop Menu =====" << endl
         << " 1. Display all drones" << endl
         << " 2. Sort by ID" << endl
         << " 3. Sort by battery" << endl
         << " 4. Sort by name" << endl
         << " 5. Shuffle fleet" << endl
         << " 6. Search by name" << endl
         << " 7. Search by ID" << endl
         << " 8. Find nearest available drone" << endl
         << " 9. Dispatch a delivery" << endl
         << "10. Recharge a drone" << endl
         << "11. Fleet status summary" << endl
         << "12. Process orders file" << endl
         << "13. Write fleet to file" << endl
         << "14. Add a new drone" << endl
         << " 0. Quit" << endl;
}

int main()
{
    login();

    Fleet fleet;
    loadFleet(fleet, "drones.txt");

    int choice = -1;
    while (choice != 0)
    {
        showMenu();
        cout << "Choose an option: ";
        cin >> choice;

        while (cin.fail()){
            if (cin.eof()){                         //input ended: exit instead of looping forever
                cout << "\nInput ended. Goodbye!" << endl;
                return 0;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');   //clear buffer
            cout << "Invalid input. Please enter a number." << endl;
            cout << "Choose an option: ";
            cin >> choice;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');       //discard leftovers like "abc" in "3abc"

        if (choice < 0 || choice > 14){
            cout << "Invalid option." << endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            fleet.displayAll();
            break;
        // TODO: cases 2 to 14 (table in Section 5)
        case 2:
            fleet.selectionSortByID();
            break;

        case 3:
            fleet.insertionSortByBattery();
            break;

        case 4:
            fleet.sortByName();
            break;

        case 5:
        {
            cout << "Enter a seed for shuffling: " << endl;
            unsigned long long seed;
            cin >> seed;
            fleet.shuffleFleet(seed);
            break;
        }

        case 6:
        {
            cout << "Enter a name to search for: " << endl;
            string name;
            cin >> name;
            int index = fleet.linearSearchByName(name);
            if (index != -1){ //-1 means that the name was not found in the list
                fleet.displayDrone(index);
            }
            else{
                cout << "Drone with name " << name << " not found." << endl;
            }
            break;
        }
        
        case 7:
        {
            cout << "Enter an ID to search for: " << endl;
            int id;
            cin >> id;
            int index2 = fleet.binarySearchByID(id);
            if (index2 != -1){ //-1 means that the ID was not found in the list
                fleet.displayDrone(index2);
            }
            else{
                cout << "Drone with ID " << id << " not found." << endl;
            }
            break;
        }

        case 8:
        {
            cout << "Enter x, y coordinates and weight: " << endl;
            int x, y;
            double weight;
            cin >> x >> y >> weight;

            int idx = fleet.findNearestAvailable(x, y, weight);
            if (idx != -1){
                fleet.displayDrone(idx);
            }
            else{
                cout << "No available drone found." << endl;
            }
            break;
        }

        case 9:
        {
            cout << "Enter x, y coordinates and weight: " << endl;
            int dx, dy;
            double dweight;
            cin >> dx >> dy >> dweight;
 
            int idx = fleet.findNearestAvailable(dx, dy, dweight);
            if (idx == -1){                         //-1 means NO drone can deliver
                cout << "No available drone found." << endl;
                break;
            }
            cout << "Nearest available drone found (before delivery): " << endl;
            fleet.displayDrone(idx);
 
            if (fleet.dispatchDrone(idx, dx, dy, dweight)){
                cout << "Drone dispatched successfully. After delivery: " << endl;
                fleet.displayDrone(idx);
            }
            else{
                cout << "Failed to dispatch delivery." << endl;
            }
            break;
        }

        case 10:
        {
            cout << "Enter the ID of the drone to recharge: " << endl;
            int rechargeID;
            cin >> rechargeID;

            if (fleet.rechargeDrone(rechargeID)){   //prints its own message when it fails
                cout << "Drone " << rechargeID << " recharged to 100% and set to IDLE." << endl;
            }
            break;
        }

        case 11:
            fleet.countByStatus();
            break;
        
        case 12:
            fleet.processOrders("orders.txt", "delivery_log.txt");
            break;
        
        case 13:
        {
            fleet.writeFleetToFile("fleet_output.txt");
            cout << "Fleet written to fleet_output.txt" << endl;
            break;
        }

        case 14:
        {
            cout << "Enter drone details (name id model battery maxPayload x y status): " << endl;
            string newName, newModel, newStatus;
            int newId, newX, newY;
            double newBattery, newMaxPayload;
            cin >> newName >> newId >> newModel >> newBattery >> newMaxPayload >>
            newX >> newY >> newStatus;

            Drone newDrone;
            //mutators one by one to check validity of each input
            newDrone.setName(newName);
            newDrone.setID(newId);
            bool ok = true; //this boolean is used to check validity 
            ok = newDrone.setID(newId) && ok;       
            ok = newDrone.setModel(newModel) && ok;
            ok = newDrone.setBattery(newBattery) && ok;
            ok = newDrone.setMaxPayload(newMaxPayload) && ok;
            ok = newDrone.setPosition(0, newX) && ok;
            ok = newDrone.setPosition(1, newY) && ok;
            ok = newDrone.setStatus(newStatus) && ok;

            if (!ok){
                cout << "Invalid drone details. Drone not added." << endl;
                break;
            }

            if (fleet.addDrone(newDrone)){ //will check for duplicate drones
                cout <<"Drone added succesfully!" << endl;
            }
            break;
        }

        case 0:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid option." << endl;
        }
    }
    return 0;
}
