#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
using namespace vex;

void autonPlanC()
{
    Controller1.Screen.print("Plan C");
    pid_Init();
    mogoGOUP();
    Imu.setHeading(270,degrees);
    
    //Auton Start Here
    drive_w_PID(reverse, 25.5, inches, 70);
    mogoGODOWN();
    wait(0.5, seconds);
    Intake.spin(forward);
    turn_to_heading(177);
    drive_w_PID(forward, 24, inches);    
    turn_to_heading(90);
    drive_w_PID(reverse, 4, inches); 
    mogoGOUP();
    drive_w_PID(forward, 4, inches);
    turn_to_heading(275);
    drive_w_PID(reverse, 16.5, inches);
    mogoGODOWN();
    drive_w_PID(forward, 4, inches);
    Lift.spinToPosition(720, degrees, false);
    turn_to_heading(340);
    drive_w_PID(forward, 30, inches);
    turn_to_heading(45);
    drive_w_PID(forward, 9, inches);
    Lift.spinToPosition(580, degrees, false);


    pid_Ends();
}
