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
    drive_w_PID(reverse, 30.8, inches, 50);
    turn_to_heading(120);
    drive_w_PID(reverse, 20, inches, 50);
    mogoGODOWN();
    wait(0.5, seconds);
    Intake.spin(forward);
    turn_to_heading(90);
    drive_w_PID(forward, 25, inches);
    mogoGOUP();
    Intake.stop();
    wait(1.5, sec);
    turn_to_heading(177);
    drive_w_PID(reverse, 26, inches);
    mogoGODOWN();
    Intake.spin(forward);
    turn_to_heading(40);
    drive_w_PID(forward, 21, inches, 40);
    Doinker.set(true);
    wait(0.2, seconds);
    drive_w_PID(reverse, 13, inches, 40);
    Doinker.set(false);
    turn_to_heading(335);
    drive_w_PID(forward, 13, inches);

    pid_Ends();


}