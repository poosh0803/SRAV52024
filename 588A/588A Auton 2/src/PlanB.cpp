#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "vex_units.h"
using namespace vex;

void autonPlanB()
{
    Controller1.Screen.print("Plan B");
    mogoGOUP();    //mogo clip spin up
    Imu.setHeading(0, degrees);
    Lift.setPosition(0,degrees);
    pid_Init();

    Lift.spinToPosition(1100, degrees, false);
    drive_w_PID(reverse, 15, inches, 50);
    turn_to_heading(30);
    turn_to_heading(30);
    drive_w_PID(forward, 5, inches, 50);
    Lift.spinToPosition(700, degrees);
    drive_w_PID(reverse, 6, inches, 50);
    Lift.spinToPosition(0, degrees, false);
    turn_to_heading(75);
    drive_w_PID(reverse, 37, inches, 50);
    mogoGODOWN();
    wait(500,msec);
    drive_w_PID(reverse, 5, inches, 50);
    turn_to_heading(355);
    intakeSTART();
    drive_w_PID(forward, 28, inches, 50);
    turn_to_heading(270);
    turn_to_heading(270);
    drive_w_PID(forward, 12, inches, 50);
    wait(100,msec);
    drive_w_PID(reverse, 5, inches, 30);
    turn_to_heading(130);
    drive_w_PID(forward, 22, inches, 70);
}
