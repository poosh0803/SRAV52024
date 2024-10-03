#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "../include/preAuton.h"
using namespace vex;

void autonPlanA()
{
    //Red Team Right Side
    pid_Init();
    mogo.set(true);
    Imu.setHeading(270,degrees);
    Stage0();
    Stage1();
    Stage2();

    pid_Ends();
}

void Stage0()
{
    turnToHeading2(0);
    wait(0.1, sec);
    driveFor2(reverse, 12, inches, 70);
    mogo.set(false);
    turnToHeading2(90);
    wait(0.1, sec);
    rollerStart();
}

void Stage1()
{
    driveFor2(forward, 10, inches, 70);
    turnToHeading2(-45);
    wait(0.1, sec);
    driveFor2(reverse, 23, inches, 70);
    mogoCorrection(false, 4);
    driveFor2(reverse, 2, inches, 70);
    turnToHeading2(180);
    wait(0.1, sec);
    driveFor2(forward, 24, inches, 70);
    wait(1, sec);
    mogo.set(true);
}

void Stage2() 
{
    Lift.spinFor(-650, degrees, false);
    driveFor2(reverse, 24, inches, 70);
    turnToHeading2(45);
    wait(0.1, sec);
    driveFor2(forward, 24, inches, 70);
    Lift.spinFor(580, degrees, false);
}