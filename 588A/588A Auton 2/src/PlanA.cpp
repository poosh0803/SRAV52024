#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "vex_units.h"
using namespace vex;

void autonPlanA()
{
    Lift.spinToPosition(-100, degrees, false);
    
    Controller1.Screen.print("Plan A");
    mogoGOUP();    //mogo clip spin up
    Imu.setHeading(315, degrees);
    pid_Init();

    Lift.spinToPosition(850, degrees);
    Lift.spinToPosition(1100, degrees, false);

    setMotorPos(360, 0);

    Lift.spinToPosition(0, degrees, false);
    drive_w_PID(reverse, 1, inches);

    // wait(1,sec);
    // Intake.setVelocity(40,percent);
    // Intake.spin(reverse);
    // Intake.stop();
    // drive_w_PID(forward, 10, inches);
    // Intake.setVelocity(100,percent);
    // Intake.spin(forward);
    // turn_to_heading(226);
    // drive_w_PID(reverse, 31, inches, 70);
    // mogoGODOWN();       //clip mogo(go down)

    // turn_to_heading(2);
    // drive_w_PID(forward, 24.5, inches);   //intake 1 ring
    // turn_to_heading(85);
    // drive_w_PID(forward, 15, inches);    //intake 1 ring
    // wait(1,sec);
    // turn_to_heading(13);     //turn to hang bar
    // wait(1,sec);
    // drive_w_PID(reverse, 35.2, inches);        //touch the hang bar
    // // turn_to_heading(5);     //turn to hang bar
    // // drive_w_PID(reverse, 5, inches);        //touch the hang bar

    pid_Ends();
}