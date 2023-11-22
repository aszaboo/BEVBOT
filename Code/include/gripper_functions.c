/*
This file contains all functions used to deliver the drink onto the table
*/

// constant for distance from UltraSonic sensor to from of the gripper
const float DIST_TO_GRIPPER = 11.75;
const float GRIPPER_LENGTH = 6.75;
const int LIFT_ENC_VALUE = 1800;
const int PLACE_CUP_VALUE = 40;


void liftGripper(bool up)
{
    int direction = 1;

    if(up)
    {
        motor[motorB] = 100;
        while(nMotorEncoder[motorB] < LIFT_ENC_VALUE) {}
        motor[motorB] = 0;
    }

    else
    {
        motor[motorB] = -100;
        while(nMotorEncoder[motorB] > 0) {}
        motor[motorB] = 0;
    }
}

void placeDrink()
{
    liftGripper(1);
    drive(10);
    while(getSensorValue[S3] > (DIST_TO_GRIPPER - GRIPPER_LENGTH)) {}
    drive(0);
    motor[motorB] = -10;
    while(nMotorEncoder[motorB] < LIFT_ENC_VALUE - PLACE_CUP_VALUE) {}
    motor[motorB] = 0;
    wait1MSec(100);
    motor[motorC] = -10;
    wait1MSec(100);
    driveDistance(-10, 100)
    liftGripper(0);
}
