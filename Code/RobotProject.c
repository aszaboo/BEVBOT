

task main() 
{
    
}


// Sensor Config

void configureAllSensors()
{
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S2] = sensorEV3_Ultrasonic;
	SensorType[S3] = sensorEV3_Color;

	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);



	SensorType[S4] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[S4] = modeEV3Gyro_Calibration;
	wait1Msec(100);
	SensorMode[S4] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);


    // SensorType[S4] = sensorEV3_IR;
}

// constants for code
const float WHEEL_RAD = 2.75;


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






// waits for a button to be pressed
void waitButton(TEV3Buttons button_name)
{
	while(!getButtonPress(button_name))
	{}
	while(getButtonPress(button_name))
	{}
}

//powers both drive motors with the same power
void drive(int motor_power)
{
	motor[motorA] = motor[motorD] = motor_power;
}
//powers both motors independently
void driveBoth(int motor_power_A, int motor_power_D)
{
	motor[motorA] = motor_power_A;
	motor[motorD] = motor_power_D;
}

// drives a distance
void driveDistance(int power, float distance) {
    const int ENC_LIMIT = (distance * 180) / (2 * M_PI * WHEEL_RAD);
    drive(power);
    while (abs(nMotorEncoder[motorA]) < ENC_LIMIT) {}
    drive(0);
}

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