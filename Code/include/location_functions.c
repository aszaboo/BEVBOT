/*
This file contains table coordinates and functions for traversing to each table BEVBOT
*/

// determines the table number with the active beacon
int locateTable(int beaconSensorValue) {
    if(beaconSensorValue >= 15)
        return 1;
    else if(beaconSensorValue >= 5)
        return 2;
    else if(beaconSensorValue >= -5)
        return table 3;
    else if(beaconSensorValue >= -15)
        return 4;
    else
        return 5;
}

// drives the robot to a table ready to order
void goToTable(int tableNumber) {
    
    if(tableNumber == 1) {
        // dir to table
    } 

    if(tableNumber == 2) {
        // dir to table 2
    }

    if(tableNumber == 3) {
        // dir to table 3
    }

    if(tableNumber == 4) {
        // dir to table 4
    }

    if(tableNumber == 5) {
        // dir to table
    }
}

// returns the robot to the base location
void returnToBase(int tableNumber) {
    if(tableNumber == 1) {
        // dir to base
    } 

    if(tableNumber == 2) {
        // dir to base
    }

    if(tableNumber == 3) {
        // dir to base
    }

    if(tableNumber == 4) {
        // dir to base
    }

    if(tableNumber == 5) {
        // dir to base
    }
}