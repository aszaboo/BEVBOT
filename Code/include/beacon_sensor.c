task main()
{
	SensorMode[S4] = modeEV3IR_Calibration;


	SensorMode[S4] = modeEV3IR_Seeker;

	wait1Msec(1000);
	// int table_number = locateTable();
	int a;
	while(true){
	a = getIRBeaconDirection(S4);
	displayString(3, "Table Number %d",a);
	wait1Msec(200);
	displayString(3, "                     ");
	}
	wait1Msec(1000);
}
