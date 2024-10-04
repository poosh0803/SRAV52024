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
    Imu.setHeading(180, degrees);
    pid_Init();

    Lift.spinToPosition(850, degrees);
    Lift.spinToPosition(1100, degrees, false);

    setMotorPos(353, 0);   //350 if doesnt work
    drive_w_PID(forward, 3.4, inches);

    Lift.spinToPosition(850, degrees, false);
    Lift.spinToPosition(0, degrees);
    wait(0.001,sec);
    drive_w_PID(reverse, 2, inches);
    turn_to_heading(127);

    wait(1,sec);
    drive_w_PID(forward, 5, inches);
    Intake.setVelocity(40,percent);
    Intake.spin(reverse); 
    Intake.stop();
    drive_w_PID(forward, 4, inches);
    Intake.setVelocity(100,percent);
    Intake.spin(forward);
    turn_to_heading(226);
    drive_w_PID(reverse, 35, inches, 70);
    mogoGODOWN();       //clip mogo(go down)
    wait(0.6,sec);

    turn_to_heading(2);
    drive_w_PID(forward, 24.5, inches);   //intake 1 ring
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