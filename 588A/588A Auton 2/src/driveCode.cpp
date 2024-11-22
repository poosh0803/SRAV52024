#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "vex_motorgroup.h"
#include "vex_units.h"
#include <cstdio>
using namespace vex;

int endGameCount = 0;

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
    Lift.setStopping(hold);
}
void liftNONE()
{
    Lift.stop();
}
void endGameAct()
{

    EndGame.set(true);
    Controller1.rumble("...");

}
bool doinker = false;

void doinkerAct()
{
  if(doinker) {
    doinker = false;
    Doinker.set(false);
  } 
  else {
    doinker = true;
    Doinker.set(true);
  }
}

void controller_reg()
{
    Controller1.ButtonR1.pressed(intakeIN);
    Controller1.ButtonR1.released(intakeNONE);
    Controller1.ButtonR2.pressed(intakeOUT);
    Controller1.ButtonR2.released(intakeNONE);
    Controller1.ButtonL1.pressed(mogoUP);
    Controller1.ButtonL2.pressed(mogoDOWN);
    Controller1.ButtonRight.pressed(liftDOWN);
    Controller1.ButtonRight.released(liftNONE);
    // Controller1.ButtonDown.pressed(liftDOWN);
    // Controller1.ButtonDown.released(liftNONE);
    Controller1.ButtonY.pressed(liftUP);
    Controller1.ButtonY.released(liftNONE);
    // Controller1.ButtonLeft.pressed(liftUnlimit);
    Controller1.ButtonUp.pressed(endGameAct);
    Controller1.ButtonA.pressed(doinkerAct);
}

void driveCode_Init()
{
    controller_reg();
    task controllerLoopTask(controllerLoop);
}