#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "../include/preAuton.h"
using namespace vex;

void autonPlanB()
{
    //Blue Side Right
    pid_Init();
    mogo.set(true);
    Imu.setHeading(90,degrees);

    driveFor2(reverse, 32, inches, 50);
    mogoCorrection(false, 4);
    mogo.set(false);
    rollerStart();
    turnToHeading2(-10);
    driveFor2(forward, 30, inches, 70);
    wait(2, sec);
    rollerEnd();

    Lift.spinFor(-650, degrees, false);
    turnToHeading2(-150);
    driveFor2(forward, 30, inches, 50);
    Lift.spinFor(580, degrees);
    pid_Ends();
}