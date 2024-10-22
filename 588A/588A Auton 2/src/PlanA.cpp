#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "vex_units.h"
using namespace vex;

void autonPlanA()
{
   mogoGOUP();    //mogo clip spin up
   Imu.setHeading(0, degrees);
   Lift.setPosition(0,degrees);
   pid_Init();

   drive_w_PID(reverse, 10, inches, 50);
   turn_to_heading(90);
   turn_to_heading(90);
   drive_w_PID(reverse, 2, inches, 50);
   Intake.spin(forward);
   wait(1,sec);
   Intake.stop();
   drive_w_PID(forward, 6, inches, 50);
   turn_to_heading(75);
   drive_w_PID(reverse, 37, inches, 50);
   mogoGODOWN();
   wait(500,msec);
   drive_w_PID(reverse, 5, inches, 50);
   turn_to_heading(5);
   intakeSTART();
   drive_w_PID(forward, 28, inches, 50);
   turn_to_heading(90);
   turn_to_heading(90);
   drive_w_PID(forward, 12, inches, 50);
   wait(100,msec);
   drive_w_PID(reverse, 5, inches, 30);
   turn_to_heading(170);
   drive_w_PID(forward, 22, inches, 70);
 
   pid_Ends();
}
