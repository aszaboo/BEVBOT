/*
This file sets up the configuration for BEVBOT
*/

// Sensor Config

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