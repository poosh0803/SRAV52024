#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
using namespace vex;

void autonPlanA()
{
    Controller.Screen.print("Plan A");
    pid_Init();
    mogo.set(true);
    Imu.setHeading(270,degrees);
    
    //Auton Start Here
    driveFor2(reverse, 27, inches, 55);
    mogoCorrection(false, 5);

    mogo.set(false);
    wait(0.5, seconds);
    driveFor2(forward, getTravelDist(), inches, 70);
    Intake.spin(forward);
    turnToHeading2(177);
    driveFor2(forward, 27, inches);
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
    turnToHeading2(0);
    driveFor2(forward, 25, inches);
    turnToHeading2(50);
    driveFor2(forward, 15, inches);
    // Lift.spinToPosition(-540, degrees, false);
    Lift.setStopping(coast);

}
