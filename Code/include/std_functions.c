/*
This file contains structures, arrays, constants and trivial functions used by BEVBOT
*/

// constant variables
const float WHEEL_RAD = 2.75;

// structure

typedef struct 
{
    float index;
    float x;
    float y;
} TableDictionary;

// TableDicts

// TableDict1
struct TableDictionary t1;
t1.index = 1;
t1.x = 0;
t1.y = 0;

// TableDict2
struct TableDictionary t2;
t2.index = 2;
t2.x = 0;
t2.y = 0;

// TableDict3
struct TableDictionary t3;
t3.index = 3;
t3.x = 0;
t3.y = 0;

// TableDict4
struct TableDictionary t4;
t4.index = 4;
t4.x = 0;
t4.y = 0;

// TableDict5
struct TableDictionary t5;
t5.index = 5;
t5.x = 0;
t5.y = 0;

// Array for storing table locations
const TableDictionary table_locations[5] = {const& t1, const& t2, const& t3, const& t4, const& t5};

// Trivial functions

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

