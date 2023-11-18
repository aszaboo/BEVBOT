/*
This file contains all functions used to deliver the drink onto the table
*/

// constant for distance from UltraSonic sensor to from of the gripper
const float DIST_TO_GRIPPER = 11.75;
const int LIFT_ENC_VALUE = 1800;

void liftGripper(bool dir) 
{
    int direction = 1;
    if(!dir)
    direction = -1;

    motor[motorB] = direction * 100;
    while(nMotorEncoder[motorB] < LIFT_ENC_VALUE) {}
    motor[motorB] = 0;
}