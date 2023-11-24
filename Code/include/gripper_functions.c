/*
This file contains all functions used to deliver the drink onto the table
*/

// constant for distance from UltraSonic sensor to from of the gripper
const int LIFT_ENC_VALUE = 20000;
const int OPEN_ENC_VALUE = 3000;

void configureAllSensors()
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

}

void liftGripper(bool up)
{
	if(up)
	{
	nMotorEncoder[motorB] = 0;
	motor[motorB] = 100;
	while(nMotorEncoder[motorB] < LIFT_ENC_VALUE) {}
	motor[motorB] = 0;
}
	else if(!up)
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

task main()
{
	liftGripper(1);
	liftGripper(0);
	openGripper(1);
	
}



void placeDrink()
{
    liftGripper(0);
	wait1Msec(100);
    openGripper(1);
	wait1Msec(100);
}

/*
	configureAllSensors();
	nMotorEncoder[motorB] = 0;
	motor[motorB] = 100;
	while(!getButtonPress(buttonEnter)){}
	while(getButtonPress(buttonEnter)){}
	motor[motorB] = 0;
	displayString(3, "Encoder Value: %d", nMotorEncoder[motorB]);
	wait1Msec(10000);*/



