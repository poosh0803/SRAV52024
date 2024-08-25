#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "vex_motorgroup.h"
#include "vex_units.h"
#include <cstdio>
using namespace vex;
bool fwdIntake = false;

void toggleIntakeFwd()
{
    if (fwdIntake) {
        Intake.stop();
        fwdIntake = false;
    }
    else {
        fwdIntake = true;
        Intake.spin(forward);
    }
}

bool revToggle = false;

void toggleIntakeRev()
{
    if (revToggle) {
        Intake.stop();
        revToggle = false;
    }
    else {
        revToggle = true;
        Intake.spin(reverse);
    }
}

bool clamping = false;

void clampToggle()
{
  if(clamping) {
    clamping = false;
    mogo.set(false);
  } 
  else {
    clamping = true;
    mogo.set(true);
  }
}

void rampToAllianceStake()
{
    Lift.spinToPosition(-390, degrees);
}

void rampToNeutralStake()
{
    Lift.spinToPosition(-570, degrees);
}

void rampToIntakePos() 
{
    Lift.spinToPosition(0, degrees);
}

int controller_loop()
{
    // Deadband stops the motors when Axis values are close to zero.
    int deadband = 5;

    while (true) {
        // Get the velocity percentage of the left motor. (Axis3)
        int leftSideSpeed = Controller.Axis3.position();
        // Get the velocity percentage of the right motor. (Axis2)
        int rightSideSpeed = Controller.Axis2.position();
        // Set the speed of the left motor. If the value is less than the deadband,
        // set it to zero.
        if (abs(leftSideSpeed) < deadband) {
        // Set the speed to zero.
        LeftDriveSmart.setVelocity(0, percent);

        } 
        else {
        // Set the speed to leftMotorSpeed
            LeftDriveSmart.setVelocity(leftSideSpeed, percent);
        }

        // Set the speed of the right motor. If the value is less than the deadband,
        // set it to zero.
        if (abs(rightSideSpeed) < deadband) {
        // Set the speed to zero
        RightDriveSmart.setVelocity(0, percent);
        } 
        else {
        // Set the speed to rightMotorSpeed
        RightDriveSmart.setVelocity(rightSideSpeed, percent);
        }

        // Spin both motors in the forward direction.
        LeftDriveSmart.spin(forward);
        RightDriveSmart.spin(forward);
        // if(fabs(Intake.current(amp)) > 2.5)
        // {
        //     Intake.stop();
        //     fwdIntake = false;
        // }

        wait(25, msec);
    }
}
int intakeMonitor()
{
    while(true)
    {
        if(fwdIntake) 
        {
            wait(200,msec);
            if(fabs(Intake.velocity(percent)) < 5)
            {
                Intake.stop();
                fwdIntake = false;
            }
        }
        else if(revToggle) 
        {
            wait(200,msec);
            if(fabs(Intake.velocity(percent)) < 5)
            {
                Intake.stop();
                revToggle = false;
            }
        }
        wait(10,msec);
    }
}

void controllerReg()
{
    task intakeMonitorTask(intakeMonitor);
    task controllerLoopTask(controller_loop);
    Controller.ButtonL1.pressed(toggleIntakeFwd);
    Controller.ButtonL2.pressed(toggleIntakeRev);
    Controller.ButtonUp.pressed(rampToAllianceStake);
    Controller.ButtonDown.pressed(rampToNeutralStake);
    Controller.ButtonR1.pressed(clampToggle);
    Controller.ButtonR2.pressed(rampToIntakePos);
}