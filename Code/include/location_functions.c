/*
This file contains table coordinates and functions for traversing to each table BEVBOT
*/

//dependencies
#include <.../include/std_functions>

// determines the table number with the active beacon
int locateTable(int beaconSensorValue) 
{

    int table_number = 0;

    if(beaconSensorValue >= 15)
        table_number = 1;

    else if(beaconSensorValue >= 5)
        table_number = 2;

    else if(beaconSensorValue >= -5)
        table_number = 3;

    else if(beaconSensorValue >= -15)
        table_number = 4;

    else
        table_number = 5;

    return table_number;
}

// drives the robot to a table ready to order
void goToTable(int const& tableNumber, TableDictionary const& tableDict) 
{
    
    if(tableNumber == 1) 
    {
        rotateRobot(tableDict[0].theta);
        wait1MSec(100);
        driveDistance(80, tableDict[0].r)
    } 

    if(tableNumber == 2) 
    {
        rotateRobot(tableDict[1].theta);
        wait1MSec(100);
        driveDistance(80, tableDict[1].r)
    }

    if(tableNumber == 3) 
    {
        rotateRobot(tableDict[2].theta);
        wait1MSec(100);
        driveDistance(80, tableDict[2].r)
    }

    if(tableNumber == 4) 
    {
        rotateRobot(tableDict[3].theta);
        wait1MSec(100);
        driveDistance(80, tableDict[3].r)
    }

    if(tableNumber == 5) 
    {
        rotateRobot(tableDict[4].theta);
        wait1MSec(100);
        driveDistance(80, tableDict[4].r)
    }
}

// returns the robot to the base location
void returnToBase(int tableNumber) 
{
    if(tableNumber == 1) 
    {
        rotateRobot(180);
        wait1MSec(100);
        driveDistance(80, tableDict[4].r)
        wait1MSec(100);
        rotateRobot(-(tableDict[0].theta));
    }

    if(tableNumber == 2)
    {
        rotateRobot(180);
        wait1MSec(100);
        driveDistance(80, tableDict[4].r)
        wait1MSec(100);
        rotateRobot(-(tableDict[1].theta));
    }

    if(tableNumber == 3) 
    {
        rotateRobot(180);
        wait1MSec(100);
        driveDistance(80, tableDict[4].r)
        wait1MSec(100);
        rotateRobot(-(tableDict[2].theta));
    }

    if(tableNumber == 4) 
    {
        rotateRobot(180);
        wait1MSec(100);
        driveDistance(80, tableDict[4].r)
        wait1MSec(100);
        rotateRobot(-(tableDict[3].theta));
    }

    if(tableNumber == 5) 
    {
        rotateRobot(180);
        wait1MSec(100);
        driveDistance(80, tableDict[4].r)
        wait1MSec(100);
        rotateRobot(-(tableDict[4].theta));
    }

}

void obstacle(int Pow, int dist, int Fulldist) 
{
	nMotorEncoder[motorC] = 0;
	
	while(nMotorEncoder[motorC] < Fulldist)
	{
    if(SensorValue(S3) > dist) {
        motor[motorC] = motor[motorD] = Pow;
    }
   else
   {
     motor[motorC] = motor[motorD] = 0;
 	 }
 }
}
