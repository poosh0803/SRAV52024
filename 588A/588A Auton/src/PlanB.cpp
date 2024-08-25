#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "vex_units.h"
using namespace vex;

void autonPlanB()
{
    mogoGOUP();
    Imu.setHeading(0, degrees);
    pid_Init();
    drive_w_PID(reverse, 12, inches, 30);
    turn_to_heading(93, 20);
    drive_w_PID(reverse, 3, inches, 30);
    Intake.setVelocity(40,percent);
    Intake.spin(forward);

    wait(1,sec);
    Intake.stop();
    drive_w_PID(forward, 10, inches);
    Intake.setVelocity(100,percent);
    Intake.spin(forward);
    turn_to_heading(226);
    drive_w_PID(reverse, 31.5, inches, 70);
    mogoGODOWN();

    turn_to_heading(2);
    drive_w_PID(forward, 24, inches);
    turn_to_heading(85);
    drive_w_PID(forward, 15, inches);
    wait(1,sec);
    turn_to_heading(13);
    drive_w_PID(reverse, 35, inches);
    pid_Ends();
}