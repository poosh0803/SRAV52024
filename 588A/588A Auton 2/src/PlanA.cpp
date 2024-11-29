#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "vex_units.h"
using namespace vex;

void autonPlanA()
{
   EndGame.set(false);
   mogoGOUP();    //mogo clip spin up
   Imu.setHeading(230, degrees);
   Lift.setPosition(0,degrees);
   pid_Init();

   drive_w_PID(forward, 6, inches, 50);
   Lift.setVelocity(80, percent);
   Lift.spinFor(reverse, 0.7, sec);
   Lift.spinToPosition(0, degrees, false);

   turn_to_heading(237);
   drive_w_PID(reverse, 31, inches, 45);
   mogoGODOWN();

   wait(500,msec);
   drive_w_PID(reverse, 5, inches, 50);
   turn_to_heading(5);
   intakeSTART();
   drive_w_PID(forward, 28, inches, 50);
   turn_to_heading(80);                      //
   turn_to_heading(80);                     //
   drive_w_PID(forward, 10.8, inches, 50);  //
   wait(100,msec);                          //
   drive_w_PID(reverse, 10.8, inches, 30);  //
   turn_to_heading(110);
   turn_to_heading(110);
   drive_w_PID(forward, 10.7, inches, 50);
   wait(100,msec);
   drive_w_PID(reverse, 5, inches, 30);
   turn_to_heading(170);
   drive_w_PID(forward, 24.8, inches, 70);
}
