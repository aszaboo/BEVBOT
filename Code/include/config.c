/*
This file sets up the configuration for BEVBOT
*/

// Sensor Config


#include "UW_sensorMux.c"

void configureAllSensors()
{

	SensorType[S1] = sensorEV3_GenericI2C;
	wait1Msec(100);

	if (!initSensorMux(msensor_S1_2, colorMeasureColor))
		return;
	if (!initSensorMux(msensor_S1_3, touchStateBump))
		return;


	SensorType[S2] = sensorEV3_Gyro;
	wait1Msec(50);
	wait1Msec(50);
	SensorMode[S2] = modeEV3Gyro_Calibration; // need to change to accommodate multi-port
	wait1Msec(100);
	SensorMode[S2] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);


	SensorType[S3] = sensorEV3_Ultrasonic;
	wait1Msec(50);
	SensorType[S4] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorType[S4] = sensorEV3_IRSensor;
	SensorType[S4] = modeEV3IR_Remote;


	SensorType[S1] = sensorEV3_Touch;
	SensorType[S2] = sensorEV3_Ultrasonic;
	SensorType[S3] = sensorEV3_Color;
	wait1Msec(50);
	SensorMode[S3] = modeEV3Color_Color;
	wait1Msec(50);
	SensorType[S4] = sensorEV3_Gyro;
    // SensorType[S4] = sensorEV3_IR;
}
