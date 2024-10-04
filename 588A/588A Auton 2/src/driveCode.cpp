#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "vex_motorgroup.h"
#include "vex_units.h"
#include <cstdio>
using namespace vex;
int liftLimit = 1700;
bool trapDoorStatues = false;
void trapDoorCheck()
{
    if(Lift.position(degrees) > 720)
    {
        if(!trapDoorStatues)
        {
            trapDoor.set(true);
            trapDoorStatues = true;
        }
    }
    else
    {
        trapDoor.set(false);
        trapDoorStatues = false;
    }
}
void liftCheck()
{
    if(Lift.position(degrees) > liftLimit && Controller1.ButtonUp.pressing())
    {
        Lift.stop();
    }
    else if(Lift.position(degrees) < 0 && Controller1.ButtonDown.pressing())
    {
        Lift.stop();
    }
}
int controllerLoop()
{
    // Deadband stops the motors when Axis values are close to zero.
    int deadband = 5;
    while (true)
    {
        int leftSideSpeed = Controller1.Axis3.position();
        int rightSideSpeed = Controller1.Axis2.position();
        // Set the speed of the left motor. If the value is less than the deadband,
        // set it to zero.
        if (abs(leftSideSpeed) < deadband) {
        // Set the speed to zero.
        LeftDrive.setVelocity(0, percent);
        } else {
        // Set the speed to leftMotorSpeed
        LeftDrive.setVelocity(leftSideSpeed, percent);
        }
        // Set the speed of the right motor. If the value is less than the deadband,
        // set it to zero.
        if (abs(rightSideSpeed) < deadband) {
        // Set the speed to zero
        RightDrive.setVelocity(0, percent);
        } else {
        // Set the speed to rightMotorSpeed
        RightDrive.setVelocity(rightSideSpeed, percent);
        }
        // Spin both motors in the forward direction.
        LeftDrive.spin(forward);
        RightDrive.spin(forward);
        trapDoorCheck();
        liftCheck();
        wait(10, msec);
    }
}
void intakeIN()
{
    Intake.spin(forward);
}
void intakeOUT()
{
    Intake.spin(reverse);
}
void intakeNONE()
{
    Intake.stop();
}
void mogoUP()
{
    Clamp.set(true);
}
void mogoDOWN()
{
    Clamp.set(false);
}
void liftUP()
{
    Lift.spin(forward);
    Lift.setStopping(hold);
}
void liftDOWN()
{
    Lift.spin(reverse);
}
void liftNONE()
{
    Lift.stop();
}
int liftLock = 2;
void liftUnlimit()
{
    if(liftLock > 0) {liftLock--; return;}
    liftLimit = 1800;
    Controller1.rumble("..");
}
void controller_reg()
{
    Controller1.ButtonR1.pressed(intakeIN);
    Controller1.ButtonR1.released(intakeNONE);
    Controller1.ButtonR2.pressed(intakeOUT);
    Controller1.ButtonR2.released(intakeNONE);
    Controller1.ButtonL1.pressed(mogoUP);
    Controller1.ButtonL2.pressed(mogoDOWN);
    Controller1.ButtonUp.pressed(liftUP);
    Controller1.ButtonUp.released(liftNONE);
    Controller1.ButtonDown.pressed(liftDOWN);
    Controller1.ButtonDown.released(liftNONE);
    Controller1.ButtonLeft.pressed(liftUnlimit);
}

void driveCode_Init()
{
    controller_reg();
    task controllerLoopTask(controllerLoop);
}