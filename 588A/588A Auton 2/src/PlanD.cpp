#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
using namespace vex;

void autonPlanD()
{
    pid_Init();
    mogoGOUP();
    Imu.setHeading(90,degrees);
    
    //Auton Start Here
    drive_w_PID(reverse, 26, inches);
    mogoGODOWN();
    wait(0.5, seconds);
    Intake.spin(forward);
    turn_to_heading(183);
    drive_w_PID(forward, 24, inches);    
    turn_to_heading(270);
    drive_w_PID(reverse, 4, inches); 
    mogoGOUP();
    drive_w_PID(forward, 4, inches);
    turn_to_heading(90);
    drive_w_PID(reverse, 15, inches);
    mogoGODOWN();
    drive_w_PID(forward, 4, inches);
    Lift.spinToPosition(-720, degrees, false);
    turn_to_heading(20);
    drive_w_PID(forward, 30, inches);
    turn_to_heading(315);
    drive_w_PID(forward, 9, inches);
    Lift.spinToPosition(-580, degrees, false);


    pid_Ends();
}