// note motors flipped

const int TABLE_RADIUS = 60.0;
const int TIME_OUT = 600000;
const int LIFT_ENC_VALUE = 20000;
const int OPEN_ENC_VALUE = 2500;

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
void shutDownProcedure();

task main()
{

	SensorType[S1] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S1] = modeEV3Color_Color;
	wait1Msec(50);

	SensorType[S2] = sensorEV3_Gyro;
	resetGyro(S2);
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

	int tableDict[6] = {50, 40, 50, 0, 50, -40};

	while(!(SensorValue[S1] == (int)colorBrown))
	{

		// while there is no IRBeacon signal do nothing
		while(getIRBeaconStrength(S4)<5) {if (sensorValue[S1] == (int)colorBrown) return;}
		int table_number = locateTable(getIRBeaconDirection(S4));
		goToTable(table_number, tableDict);
		if (SensorValue[S1] == (int)colorBrown) return;
		string order = takeOrder();
		if (SensorValue[S1] == (int)colorBrown) return;
		returnToBase(table_number, tableDict);
		if (SensorValue[S1] == (int)colorBrown) return;
		openGripper(true);
		if (SensorValue[S1] == (int)colorBrown) return;
		liftGripper(true);
		if (SensorValue[S1] == (int)colorBrown) return;
		orderUp(table_number, order, tableDict);
		if (SensorValue[S1] == (int)colorBrown) return;
		placeDrink();
		if (SensorValue[S1] == (int)colorBrown) return;
		returnToBase(table_number, tableDict);
		openGripper(false);
		if (SensorValue[S1] == (int)colorBrown) return;
		clearTimer(T1);
		resetGyro(S2);
		rotate(0);
	}
	return;
}


int locateTable(int beaconSensorValue)
{
	if (beaconSensorValue < -10)
		return 4;
	else if (beaconSensorValue > 10)
		return 0;
	else
		return 2;
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
	} while (order_kind != "Coffee" && order_kind != "Margherita" && order_kind != "Dr Pepper");

	displayString(3, "                   ");
	displayString(4, "                   ");
	displayString(5, "                   ");
	displayString(6, "                   ");
	displayString(3, order_kind);
	return order_kind;
}


// makes a and delivers the order to the table
void orderUp(int tableNumber, char* order_kind, int* tableDict)
{
	displayString(3,order_kind);
	// wait for enter button to be released (p2)
	while(!getButtonPress(ENTER_BUTTON))
	{}
	openGripper(false);
	wait1Msec(200);
	drive(tableDict[1+tableNumber], tableDict[tableNumber], 50);
}

// gripper functions

void liftGripper(bool dir)
{
	if(dir)
	{
		nMotorEncoder[motorB] = 0;
		motor[motorB] = 100;
		while(nMotorEncoder[motorB] < LIFT_ENC_VALUE && sensorValue[S1] != (int) colorBrown) {}
		motor[motorB] = 0;
	}
	else
	{
		motor[motorB] = -100;
		while(nMotorEncoder[motorB] > 0 && sensorValue[S1] != (int) colorBrown) {}
		motor[motorB] = 0;
	}
}

void openGripper(bool open)
{
	if(open)
	{
		nMotorEncoder[motorA] = 0;
		motor[motorA] = 100;
		while(nMotorEncoder[motorA] < OPEN_ENC_VALUE/2 && sensorValue[S1] != (int) colorBrown) {}
		if (sensorValue[S1] == colorBrown){
			motor[motorA] = 0;
			return;
		}
		motor[motorA] = 0;
	}

	else
	{
		nMotorEncoder[motorA] = 0;
		motor[motorA] = -100;
		while(nMotorEncoder[motorA] > -OPEN_ENC_VALUE && sensorValue[S3] != (int) colorBrown) {}
		if (sensorValue[S1] == colorBrown){
			motor[motorA] = 0;
			return;
		}
		motor[motorA] = 0;
	}
}

void placeDrink()
{
	liftGripper(false);
	wait1Msec(100);
	openGripper(1);
	wait1Msec(100);
}

void drive(int heading, int distance, int speed)
{
	nMotorEncoder[motorC] = nMotorEncoder[motorD] = 0;

	const float Kp =	0.7;
	float error;

	while ((abs(nMotorEncoder[motorC] + nMotorEncoder[motorD])/2) < distance*180/PI)
	{
		error = getGyroHeading(S2)-heading;

		float correction = (Kp*error)*-1;
		float power_left = -(speed + correction);
		float power_right = -(speed - correction);

		if (SensorValue[S3] < 30)
			motor[motorC] = motor[motorD] = 0;

		else
		{
			motor[motorC] = power_left;
			motor[motorD] = power_right;
		}

		if (sensorValue[S1] == (int)colorBrown) return;
	}
	motor[motorC] = motor[motorD] = 0;
}

void reverse(int heading, int distance, int speed)
{
	nMotorEncoder[motorC] = nMotorEncoder[motorD] = 0;
	float duty = speed;

	const float Kp =	0.5;

	float error;

	bool obstacle = false;
	while (((abs(nMotorEncoder[motorC] + nMotorEncoder[motorD])/2) < distance*180/PI) && !obstacle)
	{
		error= -(getGyroHeading(S2)-heading);

		float correction = (Kp*error)*-1;
		float power_left = duty + correction;
		float power_right = duty - correction;
		motor[motorC] = power_left;
		motor[motorD] = power_right;
		if (sensorValue[S1] == colorBrown) return;
	}
	motor[motorC] = motor[motorD] = 0;
}

void rotate(int heading)
{
	if (getGyroHeading(S2) > heading -3 && getGyroHeading(S2) < heading+3)
		return;

	motor[motorC] = -15;
	motor[motorD] = 15;
	while (getGyroHeading(S2) != heading + 5 && getGyroHeading(S2) != heading -5)
	{
		if (SensorValue[S1] == colorBrown) return;
	}

	motor[motorC] = motor[motorD] = 0;
}

void returnToBase(const int tableNumber, int*tableDict)
{
	reverse(tableDict[1+tableNumber], tableDict[tableNumber], 50);
}

returnToBase();
{
	motor[motorC] = motor[motorD] = 100; 
	while(nMotorEncoder[motorC] > 0) {}
	motor[motorC] = motor[motorD] = 0; 
	rotate(0);
}

void goToTable(const int tableNumber, int* tableDict) {
	rotate(tableDict[1+tableNumber]);
	drive(tableDict[1+tableNumber], tableDict[tableNumber], 50);
}

void shutDownProcedure();
{
	returnToBase();
	liftGripper(0);	
}
