#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "vex_units.h"
using namespace vex;

void autonPlanB()
{
   EndGame.set(false);
   mogoGOUP();    //mogo clip spin up
   Imu.setHeading(130, degrees);
   Lift.setPosition(0,degrees);
   pid_Init();

   drive_w_PID(forward, 6, inches, 50);
   Lift.setVelocity(80,percent);
   Lift.spinFor(reverse, 0.7, sec);
   Lift.spinToPosition(0, degrees, false);

   turn_to_heading(123);
   drive_w_PID(reverse, 31, inches, 45);
   mogoGODOWN();

   wait(500,msec);
   drive_w_PID(reverse, 5, inches, 50);
   turn_to_heading(355);
   intakeSTART();
   drive_w_PID(forward, 28, inches, 50);
   turn_to_heading(293);                   //
   turn_to_heading(293);                    //
   drive_w_PID(forward, 10.6, inches, 50); //
   wait(100,msec);                          //
   drive_w_PID(reverse, 10.6, inches, 30);  //
   turn_to_heading(260);
   turn_to_heading(260);
   drive_w_PID(forward, 10.7, inches, 50);
   wait(100,msec);
   drive_w_PID(reverse, 5, inches, 30);
   turn_to_heading(190);
   drive_w_PID(forward, 25, inches, 70);
}
