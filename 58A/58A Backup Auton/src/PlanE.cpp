#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "../include/preAuton.h"
using namespace vex;

void autonPlanD()
{
    //Winpoint Red
    pid_Init();
    mogo.set(true);
    Imu.setHeading(0,degrees);

   driveFor2(reverse, 12, inches, 70);
   turnToHeading2(90);
   driveFor2(reverse, 6, inches, 70);
   rollerStart();
   wait(1, sec);
   rollerEnd();
   turnToHeading2(30, 70);
   driveFor2(reverse, 27, inches, 70);
   mogoCorrection();
   mogo.set(false);
   rollerStart();
   driveFor2(reverse, 2, inches, 70);
   turnToHeading2(0);
   driveFor2(forward, 28, inches, 70);
   wait(0.5, sec);
   turnToHeading2(90, 70);
   driveFor2(forward, 20, inches, 70);
   wait(0.5, sec);
   Lift.spinFor(-1300, degrees, false);
   driveFor2(reverse, 24, inches, 70);
   turnToHeading2(165, 70);
   wait(2, sec);
   driveFor2(forward, 35, inches, 70); 
   Lift.spinFor(580, degrees);
}