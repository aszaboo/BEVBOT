

// Driving Constants
const float WHEEL_RAD = 2.75;
const int TABLE_RADIUS = 100.0;
const int TIME_OUT = 600000;

// Gripper constants
const float DIST_TO_GRIPPER = 11.75;
const float GRIPPER_LENGTH = 6.75;
const int LIFT_ENC_VALUE = 1800;
const int PLACE_CUP_VALUE = 40;

// structures
typedef struct
{
    float r;
    int theta;
} coordinate;


const coordinate tableDict[4] = {{TABLE_RADIUS, -60}, {TABLE_RADIUS, -30}, {TABLE_RADIUS, 0}, {TABLE_RADIUS, 30}, {TABLE_RADIUS, 60}};


// function prototypes

// standard functions

//powers both drive motors with the same power
void drive(int motor_power);

//powers both motors independently
void driveBoth(int motor_power_A, int motor_power_D);

// drives a distance
void driveDistance(int power, float distance);

// rotates the robot by an angle of theta
void rotateRobot(int theta);

// zero's the robot with reference to the angle theta
void zeroAngle(int theta);

// location functions

// determines the table number with the active beacon

int locateTable(int beaconSensorValue);

// drives the robot to a table ready to order
void goToTable(const int tableNumber, const coordinate & tableDict);

// returns the robot to the base location
void returnToBase(int tableNumber);

// order functions

// takes the customers order
void takeOrder();

// makes a bell noise and delivers the order to the table
void orderUp(int tableNumber);

// gripper functions

// lifts the gripper up or down
void liftGripper(bool up);

// places the drink on the table
void placeDrink();

// main program

task main()
{
    while(time1[T1] < TIME_OUT)
    {
        // while there is no IRBeacon signal do nothing
        while(!getIRBeaconDirection(S4)) {}

        // locating and driving to table
        int table_number = locateTable(getIRBeaconDirection(S4));
        goToTable(table_number, tableDict);

        // taking the customers order
        takeOrder();

        // returining to the table
        returnToBase(table_number);

        // wait for order completion'
        orderUp(table_number);

        // lifting gripper
        placeDrink();

        // returning to base
        returnToBase(table_number);

        //reset timer
        clearTimer(T1);
    }

}

// standard functions

void drive(int motor_power)
{
	motor[motorA] = motor[motorD] = motor_power;
}

void driveBoth(int motor_power_A, int motor_power_D)
{
	motor[motorA] = motor_power_A;
	motor[motorD] = motor_power_D;
}

void driveDistance(int power, float distance)
{
    const int ENC_LIMIT = (distance * 180) / (2 * PI * WHEEL_RAD);
    drive(power);
    while (abs(nMotorEncoder[motorA]) < ENC_LIMIT) {}
    drive(0);
}

void rotateRobot(int theta) {
    if(theta >= 0)
    {
        driveBoth(-50, 50);
        while(getGyroDegrees(S4) < theta) {}
        drive(0);
        wait1Msec(100);
        zeroAngle(theta);
    }

    else
    {
        driveBoth(50, -50);
        while(getGyroDegrees(S4) > theta) {}
        drive(0);
        wait1Msec(100);
        zeroAngle(theta);
    }
}

void zeroAngle(int theta)
{
    if(theta >= 0)
    {
        driveBoth(-5, 5);
        while(getGyroDegrees(S4) < theta) {}
        drive(0);
    }

    else
    {
        driveBoth(5, -5);
        while(getGyroDegrees(S4) > theta) {}
        drive(0);
    }
}

// location functions

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


void goToTable (const int tableNumber, const coordinate & tableDict[]) {
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


// order functions
void takeOrder()
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

    displayString(3, "Please make %f" order_kind);

}

void orderUp(int tableNumber) {
        while(!SensorValue[S1]) {}
        wait1MSec(200);
        goToTable(tableNumber);
    }
}

// gripper functions
void liftGripper(bool up)
{
    int direction = 1;

    if(up)
    {
        motor[motorB] = 100;
        while(nMotorEncoder[motorB] < LIFT_ENC_VALUE) {}
        motor[motorB] = 0;
    }

    else
    {
        motor[motorB] = -100;
        while(nMotorEncoder[motorB] > 0) {}
        motor[motorB] = 0;
    }
}

void placeDrink()
{
    liftGripper(1);
    drive(10);
    while(getSensorValue[S3] > (DIST_TO_GRIPPER - GRIPPER_LENGTH)) {}
    drive(0);
    motor[motorB] = -10;
    while(nMotorEncoder[motorB] < LIFT_ENC_VALUE - PLACE_CUP_VALUE) {}
    motor[motorB] = 0;
    wait1MSec(100);
    motor[motorC] = -10;
    wait1MSec(100);
    driveDistance(-10, 100)
    liftGripper(0);
}
