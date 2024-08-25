#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
using namespace vex;

void autonSkill()
{

    mogoGOUP();
    Imu.setHeading(270, degrees);
    pid_Init();
    drive_w_PID(reverse, 7, inches);
    mogoGODOWN();
    turn_to_heading(90);
    intakeSTART();
    drive_w_PID(forward, 27, inches);
    turn_to_heading(0);
    drive_w_PID(forward, 24, inches);
    turn_to_heading(265);
    drive_w_PID(forward, 26, inches, 60);
    wait(2,sec);
    drive_w_PID(forward, 10, inches, 40);
    wait(1,sec);
    drive_w_PID(reverse, 24, inches);
    turn_to_heading(315);
    drive_w_PID(forward, 15, inches);
    wait(2,sec);

    turn_to_heading(110);
    drive_w_PID(reverse, 10, inches);
    mogoGOUP();
}