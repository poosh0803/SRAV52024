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
double gearRatio = 48.0/84.0;
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
const double KpTurn = 0.085;
const double KiTurn = 0.000028;
const double KdTurn = -0.005;
// Driving PID parameters
const double KpDrive = 0.08;
const double KiDrive = 0.0000;
const double KdDrive = 0.075;
const double timeStep = 10.0; // Time between each control loop update (in milliseconds)
//Modify for turning
const double veryCoolConstant = 5.84;
//Modify for tolerance
double tolerance = 15;
//Set Motor Position
void printPosition(double L, double R)
{
    printf("L: %.2f(%.2f), R: %.2f(%.2f)\n", LeftDriveSmart.position(degrees),L, RightDriveSmart.position(degrees),R);
}
void setMotorPos(double Left, double Right)
{
    double startTime = Brain.Timer.value();
    integralMotor1 = 0.0;
    integralMotor2 = 0.0;
    LeftDriveSmart.setPosition(0, degrees);
    RightDriveSmart.setPosition(0, degrees);
    targetLeftDrivePosition = Left;
    targetRightDrivePosition = Right;
    while (fabs(targetLeftDrivePosition - LeftDriveSmart.position(degrees)) > tolerance || fabs(targetRightDrivePosition - RightDriveSmart.position(degrees)) > tolerance)
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
void turnToHeading2(double targetHeading, double speed)
{
    turnSpeedCap = speed;
    turnANDdrive = 0;
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
void driveFor2(directionType dir, double target, distanceUnits units, double speed)
{
    driveSpeedCap = speed;
    turnANDdrive = 1;
    if(units == vex::distanceUnits::cm)
    {
        target = target * 10;
    }
    else if(units == vex::distanceUnits::in)
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
        currentMotor1Position = LeftDriveSmart.position(degrees);
        currentMotor2Position = RightDriveSmart.position(degrees);
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
        LeftDriveSmart.spin(forward, controlSignalMotor1, percent);
        RightDriveSmart.spin(forward, controlSignalMotor2, percent);
        wait(timeStep, msec);
    }
    return 0;
}
bool isMogo()
{
    bool result = (mogoSensor.hue() > 60 && mogoSensor.hue() < 70);
    return result;
}
double travelDist = 0;
void mogoCorrection(bool direction, int limit)
{
  while(isMogo() == false && travelDist + 1 <= limit)
  {
    if (direction == true)
    {
        driveFor2(forward, 1, inches, 70);
        travelDist += 1;
    }
    else
    {
        driveFor2(reverse, 1, inches, 70);
        travelDist += 1;
    }
  }
}
double getTravelDist()
{
    return travelDist;
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
    LeftDriveSmart.setPosition(0, degrees);
    LeftDriveSmart.setMaxTorque(100,percent);
    LeftDriveSmart.setStopping(hold);
    RightDriveSmart.setPosition(0, degrees);
    RightDriveSmart.setMaxTorque(100,percent);
    RightDriveSmart.setStopping(hold);
    vex::task pidLoopTask(pidLoop);
    vex::task debugMonitorTask(debugMonitor);
}
void pid_Ends()
{
    pidEnabled = false;
    LeftDriveSmart.stop();
    RightDriveSmart.stop();
}