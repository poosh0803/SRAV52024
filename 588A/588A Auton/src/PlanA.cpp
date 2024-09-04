#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "vex_units.h"
using namespace vex;

void autonPlanA()
{
    Controller1.Screen.print("Plan A");
    mogoGOUP();    //mogo clip spin up
    Imu.setHeading(0, degrees);
    pid_Init();
    drive_w_PID(reverse, 12, inches, 30);
    turn_to_heading(93, 20);
    drive_w_PID(reverse, 3.2, inches, 30);
    Intake.setVelocity(40,percent);
    Intake.spin(forward);      //score preload

    wait(1,sec);
    Intake.spin(reverse);
    Intake.stop();
    drive_w_PID(forward, 10, inches);
    Intake.setVelocity(100,percent);
    Intake.spin(forward);
    turn_to_heading(226);
    drive_w_PID(reverse, 31, inches, 70);
    mogoGODOWN();       //clip mogo(go down)

    turn_to_heading(2);
    drive_w_PID(forward, 24, inches);   //intake 1 ring
    turn_to_heading(85);
    drive_w_PID(forward, 15, inches);    //intake 1 ring
    wait(1,sec);
    turn_to_heading(13);     //turn to hang bar
    wait(1,sec);
    drive_w_PID(reverse, 35.2, inches);        //touch the hang bar
    // turn_to_heading(5);     //turn to hang bar
    // drive_w_PID(reverse, 5, inches);        //touch the hang bar

    pid_Ends();
}