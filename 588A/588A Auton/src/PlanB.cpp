#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "vex_units.h"
using namespace vex;

void autonPlanB()
{
    Controller1.Screen.print("Plan B");
    mogoGOUP();   //mogo clip spin up
    Imu.setHeading(0, degrees);
    pid_Init();
    drive_w_PID(reverse, 12, inches, 30);
    turn_to_heading(267, 20);
    drive_w_PID(reverse, 3, inches, 30);
    Intake.setVelocity(40,percent);
    Intake.spin(forward);    //score preload

    wait(1,sec);
    Intake.stop();
    drive_w_PID(forward, 10, inches);
    Intake.setVelocity(100,percent);
    Intake.spin(forward);
    turn_to_heading(134);
    drive_w_PID(reverse, 31.5, inches, 70);
    mogoGODOWN();   //clip mogo(go down)

    turn_to_heading(358);
    drive_w_PID(forward, 24, inches);  //intake 1 ring
    turn_to_heading(275);
    drive_w_PID(forward, 15, inches);    //intake 1 ring
    wait(1,sec);
    turn_to_heading(347);     //turn to hang bar
    drive_w_PID(reverse, 35, inches);        //touch the hang bar
    pid_Ends();
}   