const float WHEEL_RAD = 2.75;
const int TABLE_RADIUS = 100.0;
const int TIME_OUT = 600000;
const int LIFT_ENC_VALUE = 20000;
const int OPEN_ENC_VALUE = 3000;

int tableDict[6] = {TABLE_RADIUS, -60, TABLE_RADIUS, 0, TABLE_RADIUS, 60};

void drive(int heading, int distance, int speed);
void goToTable(const int tableNumber, int* tableDict);
void returnToBase(const int tableNumber, int*tableDict);
void rotate(int heading);
int locateTable(int beaconSensorValue);
char* takeOrder();
void orderUp(int tableNumber, char* order_kind, int* tableDict);
void liftGripper(bool dir);
void openGripper(bool open);
void placeDrink();

task main()
{

	SensorType[S1] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S1] = modeEV3Color_Color;
	wait1Msec(50);

	SensorType[S2] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[S2] = modeEV3Gyro_Calibration;
	wait1Msec(100);
	SensorMode[S2] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);

	SensorType[S3] = sensorEV3_Ultrasonic;

	SensorType[S4] = sensorEV3_IRSensor;
	wait1Msec(50);
	SensorMode[S4] = modeEV3IR_Calibration;
	wait1Msec(100);
	SensorMode[S4] = modeEV3IR_Seeker;
	wait1Msec(1000);

	while(true)
	{
		// while there is no IRBeacon signal do nothing
		while(!getIRBeaconDirection(S4)) {}

		// locating and driving to table
		int table_number = locateTable(getIRBeaconDirection(S4));
		goToTable(table_number, tableDict);

		// taking the customers order
		char* order = takeOrder();

		// returining to the table
		returnToBase(table_number, tableDict);

		// wait for order completion'
		orderUp(table_number, order, tableDict);

		// lifting gripper
		placeDrink();

		// returning to base
		returnToBase(table_number, tableDict);

		liftGripper(1);

		//reset timer
		clearTimer(T1);
	}
	return;
}


int locateTable(int beaconSensorValue)
{
	if (beaconSensorValue < -9)
		return 0;
	if (beaconSensorValue > 9)
		return 2;
	else
		return 1;
}


char* takeOrder()
{

	string order_kind;

	displayString(3, "Please scan your order.");
	displayString(4, "Red: Coffee");
	displayString(5, "Blue: Margherita");
	displayString(6, "Yellow: Dr Pepper");

	do
	{
		if(SensorValue[S1] == (int)colorRed) {
			order_kind = "Coffee";
		}
		else if(SensorValue[S1] == (int)colorBlue)
		{
			order_kind = "Margherita";
		}
		else if(SensorValue[S1] == (int)colorYellow)
		{
			order_kind = "Dr Pepper";
		}
		else
		{
			displayString(3, "Sorry, we do not have that drink");
			wait1Msec(1000);
		}
	} while (order_kind != "Coffee" || order_kind != "Margherita" || order_kind != "Dr Pepper");
	return order_kind;
}


// makes a and delivers the order to the table
void orderUp(int tableNumber, char* order_kind, int* tableDict)
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
	if(dir)
	{
		nMotorEncoder[motorB] = 0;
		motor[motorB] = 100;
		while(nMotorEncoder[motorB] < LIFT_ENC_VALUE) {}
		motor[motorB] = 0;
	}
	else if(!dir)
	{
		motor[motorB] = -100;
		while(nMotorEncoder[motorB] > LIFT_ENC_VALUE) {}
		motor[motorB] = 0;
	}
}

void openGripper(bool open)
{
	if(open)
	{
		nMotorEncoder[motorA] = 0;
		motor[motorA] = 100;
		while(nMotorEncoder[motorA] < OPEN_ENC_VALUE) {}
		motor[motorA] = 0;
	}

	if(!open)
	{
		motor[motorA] = -100;
		while(nMotorEncoder[motorA] > 0) {}
		motor[motorA] = 0;
	}
}

void placeDrink()
{
	liftGripper(0);
	wait1Msec(100);
	openGripper(1);
	wait1Msec(100);
}

void drive(int heading, int distance, int speed)
{

	nMotorEncoder[motorC] = nMotorEncoder[motorD] = 0;

	const float Kp =	0.5;
	float error;

	while ((abs(nMotorEncoder[motorC] + nMotorEncoder[motorD])/2) < distance*180/PI)
	{
		error = getGyroHeading(S2)-heading;

		float correction = (Kp*error)*-1;
		float power_left = -(speed + correction);
		float power_right = -(speed - correction);

		if (SensorValue[S3] < 15)
			motor[motorC] = motor[motorD] = 0;

		else
		{
			motor[motorC] = power_left;
			motor[motorD] = power_right;
		}
	}
	motor[motorC] = motor[motorD] = 0;
}

void reverse(int heading, int distance, int speed)
{

	nMotorEncoder[motorC] = nMotorEncoder[motorD] = 0;
	const float Kp =	0.5;

	float error;

	bool obstacle = false;
	while (((abs(nMotorEncoder[motorC] + nMotorEncoder[motorD])/2) < distance*180/PI) && !obstacle)
	{
		error = -(getGyroHeading(S2)-heading);
		float correction = (Kp*error)*-1;
		float power_left = speed + correction;
		float power_right = speed - correction;

		if (SensorValue[S3] < 15)
			motor[motorC] = motor[motorD] = 0;
		else
		{
			motor[motorC] = power_left;
			motor[motorD] = power_right;
		}
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
