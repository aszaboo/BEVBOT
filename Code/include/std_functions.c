/*
This file contains structures, arrays, constants and trivial functions used by BEVBOT
*/

// constant variables
const float WHEEL_RAD = 2.75;
const int TABLE_RADIUS = 100;
const int TIME_OUT = 600000;

// structures
typedef struct 
{
    float r;
    int theta;
} TableDictionary;

// TableDicts - all points are relative to the base location

// TableDict1
struct TableDictionary t1;
t1.r = TABLE_RADIUS;
t1.theta = 30;

// TableDict2
struct TableDictionary t2;
t2.r = TABLE_RADIUS;
t2.theta = 60;

// TableDict3
struct TableDictionary t3;
t3.r = TABLE_RADIUS;
t3.theta = 90;

// TableDict4
struct TableDictionary t4;
t4.r = TABLE_RADIUS;
t4.theta = 120;

// TableDict5
struct TableDictionary t5;
t5.r = TABLE_RADIUS;
t5.theta = 150;

// Array for storing table locations
const TableDictionary table_locations[5] = {const& t1, const& t2, const& t3, const& t4, const& t5};

// Trivial functions

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
        while(getGyroDegrees(s4) < theta) {}
        drive(0);
        wait1MSec(100);
        zeroAngle(theta);
    }

    else 
    {
        driveBoth(50, -50);
        while(getGyroDegrees(s4) > theta) {}
        drive(0);
        wait1MSec(100);
        zeroAngle(theta);
    }
}

// zero's the robot with reference to the angle theta
void zeroAngle(int theta)
{
    if(theta >= 0) 
    {
        driveBoth(-5, 5);
        while(getGyroDegrees(s4) < theta) {}
        drive(0);
    }

    else 
    {
        driveBoth(5, -5);
        while(getGyroDegrees(s4) > theta) {}
        drive(0);
    }
}

