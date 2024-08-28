#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
using namespace vex;

void autonPlanA()
{
    pid_Init();
    mogo.set(true);
    Imu.setHeading(270,degrees);
    
    //Auton Start Here
    driveFor2(reverse, 26, inches);
    mogo.set(false);
    wait(0.5, seconds);
    Intake.spin(forward);
    turnToHeading2(177);
    driveFor2(forward, 24, inches);    
    turnToHeading2(90);
    driveFor2(reverse, 4, inches); 
    mogo.set(true);
    driveFor2(forward, 4, inches);
    turnToHeading2(270);
    driveFor2(reverse, 16.5, inches);
    mogo.set(false);
    driveFor2(forward, 4, inches);
    Lift.spinToPosition(-720, degrees, false);
    turnToHeading2(340);
    driveFor2(forward, 30, inches);
    turnToHeading2(45);
    driveFor2(forward, 8, inches);
    Lift.spinToPosition(-580, degrees, false);


    pid_Ends();
}
