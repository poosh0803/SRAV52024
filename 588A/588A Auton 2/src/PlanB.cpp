#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "vex_units.h"
using namespace vex;

void autonPlanB()
{
   mogoGOUP();    //mogo clip spin up
   Imu.setHeading(130, degrees);
   Lift.setPosition(0,degrees);
   pid_Init();

   drive_w_PID(forward, 5.5, inches, 50);
   Lift.setVelocity(80,percent);
   Lift.spinFor(reverse, 0.6, sec);
   Lift.spinToPosition(0, degrees, false);

   turn_to_heading(123);
   drive_w_PID(reverse, 31, inches, 45);
   mogoGODOWN();

   wait(500,msec);
   drive_w_PID(reverse, 5, inches, 50);
   turn_to_heading(355);
   intakeSTART();
   drive_w_PID(forward, 28, inches, 50);
   turn_to_heading(270);
   turn_to_heading(270);
   drive_w_PID(forward, 12, inches, 50);
   wait(100,msec);
   drive_w_PID(reverse, 5, inches, 30);
   turn_to_heading(190);
   drive_w_PID(forward, 22, inches, 70);
}
