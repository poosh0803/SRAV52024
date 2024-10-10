#include "../include/vex.h"
#include "../include/robot-config.h"
#include "../include/vision.h"
#include "../include/logger.h"
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
double leftSpeedCap = 100;
double rightSpeedCap = 100;
// Target positions for each motor (adjust these based on your task)
double targetLeftDrivePosition = 0;
double targetRightDrivePosition = 0;
// Game object tracking
bool mogoTracking = false;
bool mogoFound = false;
double staleTime = 0.3;
double center = 315.0;
double visionKP = 0.075;
double startTime = Brain.Timer.value();
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
const double veryCoolConstant = 2.29;
//Modify for tolerance
double tolerance = 15;
//Set Motor Position
void printPosition(double L, double R)
{
    printf("L: %.2f(%.2f), R: %.2f(%.2f)\n", LeftDrive.position(degrees),L, RightDrive.position(degrees),R);
}
void setMotorPos(double Left, double Right)
{
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

    logVal(LOG_DEBUG, "Done in ", Brain.Timer.value() - startTime);
    mogoTracking = false;
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
void drive_w_PID(directionType dir, double target, distanceUnits units, double speed, bool trackingMogo)
{
    driveSpeedCap = speed;
    turnANDdrive = 1;
    mogoTracking = trackingMogo;
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
void curveDrive(double Ltarget, double Rtarget, vex::distanceUnits units, double Lspeed, double Rspeed)
{
    turnANDdrive = 2;
    if(units == vex::distanceUnits::cm)
    {
        Ltarget = Ltarget * 10;
        Rtarget = Rtarget * 10;
    }
    else if(units == vex::distanceUnits::in)
    {
        Ltarget = Ltarget * 25.4;
        Rtarget = Rtarget * 25.4;

    }
    double LspinValue = (Ltarget / wheelTravel / gearRatio) * 360;
    double RspinValue = (Rtarget / wheelTravel / gearRatio) * 360;
    leftSpeedCap = Lspeed;
    rightSpeedCap = Rspeed;
    setMotorPos(LspinValue, RspinValue);
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
    double mogoAngle, mogoAnglePrev;

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
            
            // Mogo tracking
            if (mogoTracking) {
                mogoAngle = Vision::getMogoAngle();

                if (mogoAngle != 0) {
                    mogoAnglePrev = mogoAngle;
                    controlSignalMotor1 += mogoAnglePrev;
                    controlSignalMotor2 -= mogoAnglePrev;
                }

            }
        }
        else if(turnANDdrive == 2)
        {
            controlSignalMotor1 = calculateControlSignal(targetLeftDrivePosition, currentMotor1Position, prevErrorMotor1, integralMotor1,KpDrive, KiDrive, KdDrive);
            controlSignalMotor2 = calculateControlSignal(targetRightDrivePosition, currentMotor2Position, prevErrorMotor2, integralMotor2,KpDrive, KiDrive, KdDrive);
            if(controlSignalMotor1 > leftSpeedCap) {controlSignalMotor1 = leftSpeedCap;}
            else if(controlSignalMotor1 < -leftSpeedCap) {controlSignalMotor1 = -leftSpeedCap;}
            if(controlSignalMotor2 > rightSpeedCap) {controlSignalMotor2 = rightSpeedCap;}
            else if(controlSignalMotor2 < -rightSpeedCap) {controlSignalMotor2 = -rightSpeedCap;}
            
        }
        LeftDrive.spin(forward, controlSignalMotor1, percent);
        RightDrive.spin(forward, controlSignalMotor2, percent);
        wait(timeStep, msec);
    }
    return 0;
}
int debugMonitor()
{
    int prevMogoTrackStatus = Vision::LOST;
    while(true)
    {
        logVal(LOG_INFO, "Heading: ", (double)Imu.heading(degrees));

        if (Vision::mogoTrackStatus == Vision::TRACKING && prevMogoTrackStatus != Vision::mogoTrackStatus) {
            logVal(LOG_DEBUG, "Mogo tracking");
            prevMogoTrackStatus = Vision::mogoTrackStatus;
        } else if (Vision::mogoTrackStatus == Vision::STALE && prevMogoTrackStatus != Vision::mogoTrackStatus) {
            logVal(LOG_WARNING, "Mogo stale");
            prevMogoTrackStatus = Vision::mogoTrackStatus;
        } else if (Vision::mogoTrackStatus == Vision::LOST && prevMogoTrackStatus != Vision::mogoTrackStatus) {
            logVal(LOG_ERROR, "Mogo lost");
            prevMogoTrackStatus = Vision::mogoTrackStatus;
        }

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