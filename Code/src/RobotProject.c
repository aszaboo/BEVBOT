#include <.../include/config.c>
#include <.../include/drive_functions.c>
#include <.../include/order_functions.c>
#include <.../include/std_functions.c>

task main() 
{
    
}


// float measureTableHeight()


// navigates to the table based on the IR sensor values
void navigateToTable(int ir_value) 
{

    // creating the file to store the direction to the table
    //ofstream FileOut("DirectionFile.txt");

    //backup ten cm and turn around
    driveDistance(-50, 10);
    driveBoth(50, -50);

    // resetting the motor encoder value

    // getting the direction and the strength of the IR sensor
    int table_direction = getIRBeaconDirection(S...);
 
    //Infinite loop
    while(!SensorValue[S1])
    {
        while(true) 
        {
        //If the IR sensor (port 4) sees a beacon to the right (positive)
        if(table_direction > 5)
        {
            //Turn Right
            setMotorSpeed(leftMotor, 50);
            setMotorSpeed(rightMotor, -50);
        }
        //If the IR sensor (port 4) sees a beacon to the left (negative)
        else if(table_direction < -5)
        {
            //Turn Left
            setMotorSpeed(leftMotor, -50);
            setMotorSpeed(rightMotor, 50);
        }
        //Otherwise, move forward 
        else
        {
            //Move Forward
            setMotorSpeed(leftMotor, 50);
            setMotorSpeed(rightMotor, 50);
        }

        } // infinite loop

    } // while loop

    int table_distance = nMotorEncoder[motorA];
    return table_direction;
    return table_distance;
    
} // navigateToTable
















// makes a bell noise and delivers the order to the table
void orderUp(bool touchSensorInput, int tableNumber) {
    if(touchSensorInput) {
        // play sound from EV3
        wait1MSec(200);
        goToTable(tableNumber);
    }
}

// takes the customers order
takeOrder(int color) 
{

    string order_kind = " ";

    do {

    displayString(3, "Please scan your order");

    if(SensorValue[S3] = (int)colorRed) {
    order_kind = "Coke";

    else if(SensorValue[S3] = (int)colorBlue)
    order_kind = "Raspberry Lemonade";

    else if(SensorValue[S3] = (int)colorYellow)  
    order_kind = "Lemonade";

    else displayString(3, "Not a valid order type");

    } while(order_kind = " ");

    } // takeOrder

    displayString(3, order_kind);


}