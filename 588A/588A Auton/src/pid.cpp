#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "vex_task.h"
#include "vex_units.h"
#include <cstdio>
#include <cmath>
#include <utility>
using namespace vex;
int turnANDdrive = 0;
bool pidEnabled = false;
double gearRatio = 72.0/48.0;
double wheelTravel = 320;
double driveSpeedCap = 100;
double turnSpeedCap = 100;
// Target positions for each motor (adjust these based on your task)
double targetLeftDrivePosition = 0;
double targetRightDrivePosition = 0;
// Variables for PID control
double prevErrorMotor1 = 0.0;
double integralMotor1 = 0.0;
double prevErrorMotor2 = 0.0;
double integralMotor2 = 0.0;
// Variables for motion profile control
double currentVelocityMotor1 = 0.0;
double currentVelocityMotor2 = 0.0;
// Turning PID parameters
const double KpTurn = 0.26;
const double KiTurn = 0.000;
const double KdTurn = -0.12;
// Driving PID parameters
const double KpDrive = 0.234;
const double KiDrive = 0.000;
const double KdDrive = 0.35;
const double timeStep = 10.0; // Time between each control loop update (in milliseconds)
//Modify for turning
const double veryCoolConstant = 2.2;
//Modify for tolerance
double tolerance = 15;
//Set Motor Position
void printPosition(double L, double R)
{
    printf("L: %.2f(%.2f), R: %.2f(%.2f)\n", LeftDrive.position(degrees),L, RightDrive.position(degrees),R);
}
void setMotorPos(double Left, double Right)
{
    double startTime = Brain.Timer.value();
    integralMotor1 = 0.0;
    integralMotor2 = 0.0;
    LeftDrive.setPosition(0, degrees);
    RightDrive.setPosition(0, degrees);
    targetLeftDrivePosition = Left;
    targetRightDrivePosition = Right;
    while (fabs(targetLeftDrivePosition - LeftDrive.position(degrees)) > tolerance || fabs(targetRightDrivePosition - RightDrive.position(degrees)) > tolerance)
    {
        // printPosition(targetLeftDrivePosition,targetRightDrivePosition);
        wait(20,msec);
    }
    printf("Done in %.2f sec\n", Brain.Timer.value() - startTime);
}

void turn_w_PID(turnType dir, double target)
{
    double spinValue = target * veryCoolConstant;
    turnANDdrive = 0;
    if(dir == left)
    {
        setMotorPos(-spinValue, spinValue);
    }
    else
    {
        setMotorPos(spinValue, -spinValue);
    }
}

std::pair<turnType, double> determineTurnDirection(double currentHeading, double targetHeading)
{
    // Calculate the angle difference between the current and target headings
    double angleDifference = targetHeading - currentHeading;

    // Normalize the angle difference to be within the range of -180 to 180 degrees
    while (angleDifference > 180.0) {
    angleDifference -= 360.0;
    }

    while (angleDifference <= -180.0) {
    angleDifference += 360.0;
    }

    // Determine the turn direction (left or right)
    turnType direction;
    if (angleDifference > 0) {
    direction = right;
    } else if (angleDifference < 0) {
    direction = left;
    }

    // Calculate the absolute angle to turn (in degrees)
    double angleToTurn = fabs(angleDifference);

    return std::make_pair(direction, angleToTurn);
}
void turn_to_heading(double targetHeading, double speed)
{
    turnANDdrive = 0;
    turnSpeedCap = speed;
    auto result = determineTurnDirection(Imu.heading(), targetHeading);
    turnType direction = result.first;
    double angleToTurn = result.second;
    if(direction == right)
    {
    printf("right tar: %.1f, val: %.1f\n", targetHeading, angleToTurn);
    }
    else
    {
    printf("left tar: %.1f, val: %.1f\n", targetHeading, angleToTurn);
    }
    turn_w_PID(direction, angleToTurn);
}
void drive_for_time(directionType direction, double timeLength)
{
    turnANDdrive = 1;
    setMotorPos(0, 0);
    if(direction == forward)
    {
        targetLeftDrivePosition = 999999;
        targetRightDrivePosition = 999999;
    }
    else
    {
        targetLeftDrivePosition = -999999;
        targetRightDrivePosition = -999999;
    }
    wait(timeLength, seconds);
    setMotorPos(0, 0);
}
void drive_w_PID(directionType dir, double target, distanceUnits units, double speed)
{
    driveSpeedCap = speed;
    turnANDdrive = 1;
    if(units == vex::distanceUnits::cm)
    {
        target = target * 10;
    }
    else if(units ==vex::distanceUnits::in)
    {
        target = target * 25.4;
    }
    double spinValue = (target / wheelTravel / gearRatio) * 360;
    if(dir == forward)
    {
        setMotorPos(spinValue, spinValue);
    }
    else
    {
        setMotorPos(-spinValue, -spinValue);
    }
}
// PID control function with lookahead for a single motor
double calculateControlSignal(double target, double current, double &prevError, double &integral, double Kp, double Ki, double Kd)
{
    double error = target - current;
    integral += error;
    double derivative = error - prevError;
    double pComponent = Kp * error;
    double iComponent = Ki * integral;
    double dComponent = Kd * derivative;
    double controlSignal = pComponent + iComponent + dComponent;
    prevError = error;
    return controlSignal;
}
int pidLoop()
{
    double controlSignalMotor1;
    double controlSignalMotor2;
    double currentMotor1Position;
    double currentMotor2Position;
    while (pidEnabled)
    {
        currentMotor1Position = LeftDrive.position(degrees);
        currentMotor2Position = RightDrive.position(degrees);
        if(turnANDdrive == 0)
        {
            controlSignalMotor1 = calculateControlSignal(targetLeftDrivePosition, currentMotor1Position, prevErrorMotor1, integralMotor1,KpTurn, KiTurn, KdTurn);
            controlSignalMotor2 = calculateControlSignal(targetRightDrivePosition, currentMotor2Position, prevErrorMotor2, integralMotor2,KpTurn, KiTurn, KdTurn);
            if(controlSignalMotor1 > turnSpeedCap) {controlSignalMotor1 = turnSpeedCap;}
            else if(controlSignalMotor1 < -turnSpeedCap) {controlSignalMotor1 = -turnSpeedCap;}
            if(controlSignalMotor2 > turnSpeedCap) {controlSignalMotor2 = turnSpeedCap;}
            else if(controlSignalMotor2 < -turnSpeedCap) {controlSignalMotor2 = -turnSpeedCap;}
        }
        else if(turnANDdrive == 1)
        {
            controlSignalMotor1 = calculateControlSignal(targetLeftDrivePosition, currentMotor1Position, prevErrorMotor1, integralMotor1,KpDrive, KiDrive, KdDrive);
            controlSignalMotor2 = calculateControlSignal(targetRightDrivePosition, currentMotor2Position, prevErrorMotor2, integralMotor2,KpDrive, KiDrive, KdDrive);
            if(controlSignalMotor1 > driveSpeedCap) {controlSignalMotor1 = driveSpeedCap;}
            else if(controlSignalMotor1 < -driveSpeedCap) {controlSignalMotor1 = -driveSpeedCap;}
            if(controlSignalMotor2 > driveSpeedCap) {controlSignalMotor2 = driveSpeedCap;}
            else if(controlSignalMotor2 < -driveSpeedCap) {controlSignalMotor2 = -driveSpeedCap;}
            
        }
        LeftDrive.spin(forward, controlSignalMotor1, percent);
        RightDrive.spin(forward, controlSignalMotor2, percent);
        wait(timeStep, msec);
    }
    return 0;
}
int debugMonitor()
{
    while(true)
    {
        printf("Heading: %.2f\n", (float)Imu.heading(degrees));
        wait(50,msec);
    }
}
void pid_Init()
{
    pidEnabled = true;
    LeftDrive.setPosition(0, degrees);
    LeftDrive.setMaxTorque(100,percent);
    LeftDrive.setStopping(hold);
    RightDrive.setPosition(0, degrees);
    RightDrive.setMaxTorque(100,percent);
    RightDrive.setStopping(hold);
    vex::task pidLoopTask(pidLoop);
    vex::task debugMonitorTask(debugMonitor);
}
void pid_Ends()
{
    pidEnabled = false;
    LeftDrive.stop();
    RightDrive.stop();
}