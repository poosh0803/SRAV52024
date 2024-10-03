#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
using namespace vex;

void autonPlanC()
{
    Controller.Screen.print("Plan C");
    pid_Init();
    mogo.set(true);
    Imu.setHeading(90,degrees);
    
    //Auton Start Here
    driveFor2(reverse, 26, inches, 50);
    mogoCorrection(false, 10);

    mogo.set(false);
    wait(0.5, seconds);
    driveFor2(forward, getTravelDist(), inches, 70);
    Intake.spin(forward);
    turnToHeading2(183);
    driveFor2(forward, 26, inches);
    wait(3,sec);
    // turnToHeading2(90);
    // driveFor2(reverse, 4, inches); 
    // mogo.set(true);
    // driveFor2(forward, 4, inches);
    // turnToHeading2(270);
    // driveFor2(reverse, 16.5, inches);
    // mogo.set(false);
    // driveFor2(forward, 4, inches);
    Lift.spinToPosition(-650, degrees, false);
    turnToHeading2(270);
    driveFor2(forward, 10, inches);
    turnToHeading2(350);
    driveFor2(forward, 25, inches);
    Lift.spinToPosition(-540, degrees, false);


    pid_Ends();
}