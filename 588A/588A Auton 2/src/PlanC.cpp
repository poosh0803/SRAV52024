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
    drive_w_PID(reverse, 30.8, inches, 50);
    turn_to_heading(240);
    drive_w_PID(reverse, 19, inches, 50);
    mogoGODOWN();
    wait(0.5, seconds);
    Intake.spin(forward);
    turn_to_heading(270);
    drive_w_PID(forward, 24.5, inches);
    mogoGOUP();
    Intake.stop();
    wait(1.5, sec);
    turn_to_heading(182);
    drive_w_PID(reverse, 26, inches);
    mogoGODOWN();
    Intake.spin(forward);
    turn_to_heading(320);
    drive_w_PID(forward, 21, inches, 40);
    Doinker.set(true);
    wait(0.2, seconds);
    drive_w_PID(reverse, 13, inches, 40);
    Doinker.set(false);
    turn_to_heading(25);
    drive_w_PID(forward, 13, inches);

    pid_Ends();
}
