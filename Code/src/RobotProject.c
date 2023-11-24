

// Driving Constants
const float WHEEL_RAD = 2.75;
const int TABLE_RADIUS = 100.0;
const int TIME_OUT = 600000;

// Gripper constants
const float DIST_TO_GRIPPER = 11.75;
const float GRIPPER_LENGTH = 6.75;
const int LIFT_ENC_VALUE = 1800;
const int PLACE_CUP_VALUE = 40;


int tableDict[6] = {TABLE_RADIUS, -60, TABLE_RADIUS, 0, TABLE_RADIUS, 60};


// function prototypes

// standard functions
void drive(int heading, int distance, int speed);
void goToTable(const int tableNumber, int* tableDict);
void returnToBase(const int tableNumber, int*tableDict);
void rotate(int heading);

// location functions

// determines the table number with the active beacon

int locateTable(int beaconSensorValue);

// order functions

// takes the customers order
void takeOrder();

// makes a bell noise and delivers the order to the table
void orderUp(int tableNumber, int* tableDict);

// gripper functions

// lifts the gripper up or down
void liftGripper(bool dir);

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
        returnToBase(table_number, tableDict);

        // wait for order completion'
        orderUp(table_number, tableDict);

        // lifting gripper
        placeDrink();

        // returning to base
        returnToBase(table_number, tableDict);

        //reset timer
        clearTimer(T1);
    }

}

// standard functions

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

// takes a persons order and returns the order as a string
string takeOrder()
{

    string order_kind;

    displayString(3, "Please scan your order");

    do
    {
    if(SensorValue[S1] == (int)colorRed) {
    order_kind = "Coke";
    }
    else if(SensorValue[S1] == (int)colorBlue)
    {
    order_kind = "Raspberry Lemonade";
    }
    else if(SensorValue[S1] == (int)colorYellow)
    {
    order_kind = "Lemonade";
    }
    else
    displayString(3, "Sorry we do not have that drink");
    } while (order_kind != "Coke" || order_kind != "Raspberry Lemonade" || order_kind != "Lemonade");

    return order_kind;

}


// makes a and delivers the order to the table
void orderUp(int tableNumber, string order_kind, int* tableDict)
{
        // wait for enter button to be released (p2)
	while(!getButtonPress(buttonEnter))
  {
    displayString(3, "%s", order_kind);
	}

	while(getButtonPress(buttonEnter)) {}
  wait1Msec(200);
  goToTable(tableNumber, tableDict);
}

// gripper functions
void liftGripper(bool dir)
{
    int direction = 1;

    if(dir)
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
    liftGripper(true);
    motor[motorB] = -10;
    while(nMotorEncoder[motorB] < LIFT_ENC_VALUE - PLACE_CUP_VALUE) {}
    motor[motorB] = 0;
    wait1Msec(100);
    liftGripper(false);
}


void drive(int heading, int distance, int speed)
{

	nMotorEncoder[motorC] = nMotorEncoder[motorD] = 0;
	float duty = speed;

	const float Kp =	0.5;

	float error;

	while ((abs(nMotorEncoder[motorC] + nMotorEncoder[motorD])/2) < distance*180/PI)
	{
		error=getGyroHeading(S2)-heading;

		float correction = (Kp*error)*-1;
		float power_left = -(duty + correction);
		float power_right = -(duty - correction);

		motor[motorC] = power_left;
		motor[motorD] = power_right;

	}
	motor[motorC] = motor[motorD] = 0;
}

void reverse(int heading, int distance, int speed)
{

	nMotorEncoder[motorC] = nMotorEncoder[motorD] = 0;
	float duty = speed;

	const float Kp =	0.5;

	float error;

	while ((abs(nMotorEncoder[motorC] + nMotorEncoder[motorD])/2) < distance*180/PI)
	{
		error= -(getGyroHeading(S2)-heading);

		float correction = (Kp*error)*-1;
		float power_left = duty + correction;
		float power_right = duty - correction;

		motor[motorC] = power_left;
		motor[motorD] = power_right;

	}
	motor[motorC] = motor[motorD] = 0;
}

void rotate(int heading)
{
	motor[motorC] = -20;
	motor[motorD] = 20;
	while (getGyroHeading(S2)+180 != heading+179)
	{}
	motor[motorC] = motor[motorD] = 0;
}

void returnToBase(const int tableNumber, int*tableDict)
{
	reverse(tableDict[1+tableNumber], tableDict[tableNumber], 50);
	rotate(0);
}

void goToTable(const int tableNumber, int* tableDict) {
	rotate(tableDict[1+tableNumber]);
	drive(tableDict[1+tableNumber], tableDict[tableNumber], 50);
}
