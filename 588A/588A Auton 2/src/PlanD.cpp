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
    turn_to_heading(45);
    drive_w_PID(forward, 29, inches);
    Doinker.set(true);
    drive_w_PID(reverse, 9, inches);
    Doinker.set(false);
    drive_w_PID(forward, 9, inches);

    pid_Ends();


}