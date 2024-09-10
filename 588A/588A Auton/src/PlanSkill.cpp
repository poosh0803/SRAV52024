#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
using namespace vex;

void autonSkill()
{

    mogoGOUP();
    Imu.setHeading(303, degrees);
    pid_Init();
    drive_w_PID(reverse, 8, inches);
    mogoGODOWN();               //clip goal
    turn_to_heading(90);
    intakeSTART();
    drive_w_PID(forward, 27, inches);     //first ring
    turn_to_heading(357);
    drive_w_PID(forward, 24, inches);     ///second ring
    turn_to_heading(265);
    drive_w_PID(forward, 20, inches, 40);     //thrid ring
    drive_w_PID(forward, 6, inches, 30);// foruth ring
    wait(2,sec);
    drive_w_PID(forward, 10, inches, 40);
    wait(1,sec);
    drive_w_PID(reverse, 24, inches);   //5th ring
    turn_to_heading(315);
    drive_w_PID(forward, 15, inches);      // sixth ring
    wait(2,sec);

    turn_to_heading(110);
    drive_w_PID(reverse, 10, inches);    //go to goal
    mogoGOUP();      
    wait(0.5,sec);
    drive_w_PID(forward,7, inches);
    turn_to_heading(357);
    drive_w_PID(reverse, 74.5, inches);
    mogoGODOWN();    ///clip goal
    drive_w_PID(reverse, 8, inches);     //try to intake ring
    turn_to_heading(90);
    drive_w_PID(forward, 24, inches);
    turn_to_heading(180);
    drive_w_PID(forward, 24, inches);
    turn_to_heading(265);
}