#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
using namespace vex;

void autonPlanC()
{
    pid_Init();
    mogoGOUP();
    Imu.setHeading(270,degrees);
    
    //Auton Start Here
    drive_w_PID(reverse, 26, inches, 50);
    mogoGODOWN();
    wait(0.5, seconds);
    Intake.spin(forward);
    turn_to_heading(177);
    drive_w_PID(forward, 24, inches);    
    turn_to_heading(90);
    drive_w_PID(reverse, 4, inches); 
    wait(1,sec);
    mogoGOUP();
    drive_w_PID(forward, 7, inches);
    turn_to_heading(270);
    drive_w_PID(reverse, 15, inches);
    mogoGODOWN();
    drive_w_PID(forward, 4, inches);
    Lift.setVelocity(100,percent);
    Lift.spinToPosition(720, degrees, false);
    turn_to_heading(335);
    drive_w_PID(forward, 30, inches);
    while (Lift.position(degrees) < 700) { wait(10,msec);}
    turn_to_heading(45);
    drive_w_PID(forward, 7, inches);
    Lift.spinToPosition(550, degrees, false);

    Lift.setVelocity(50,percent);
    pid_Ends();
}
