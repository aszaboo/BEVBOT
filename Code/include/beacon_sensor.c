task main()
{
	SensorMode[S4] = modeEV3IR_Calibration;
	SensorMode[S4] = modeEV3IR_Seeker;

	wait1Msec(1000);
	// int table_number = locateTable();
	int a;
	int b;
	while(true){
	a = getIRBeaconDirection(S4);
	b = getIRBeaconStrength(S4);
	displayString(3, "direction %d",a);
	displayString(4, "strength %d",b);
	wait1Msec(200);
	displayString(3, "                     ");
	displayString(4, "                     ");
	}
	wait1Msec(1000);
}
