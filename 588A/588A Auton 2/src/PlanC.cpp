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
    turn_to_heading(183);
    drive_w_PID(reverse, 26, inches);
    mogoGODOWN();
    wait(1.5, sec);
    Intake.spin(forward);
    wait(1.5, sec);

    pid_Ends();
}
