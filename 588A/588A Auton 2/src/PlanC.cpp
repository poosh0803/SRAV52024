#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
using namespace vex;

void autonPlanC()
{
    pid_Init();
    mogoGOUP();
    Imu.setHeading(240,degrees);
    
    //Auton Start Here
    drive_w_PID(reverse, 40, inches, 50);
    mogoGODOWN();
    wait(0.5, seconds);
    Intake.spin(forward);
    turn_to_heading(180);
    drive_w_PID(forward, 30, inches);
    wait(2, sec);
    turn_to_heading(60);
    drive_w_PID(reverse, 48, inches);

    pid_Ends();
}
