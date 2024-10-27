#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "../include/logger.h"
using namespace vex;

void autonSkill()
{  
    // logVal(LOG_INFO, "Skill Start");
    //Init
    EndGame.set(false);
    mogoGOUP();
    Imu.setHeading(90, degrees);
    pid_Init();

    //Wall Stake + mogo
    Intake.spinFor(forward, 720, degrees);
    Intake.spinFor(reverse, 180, degrees);
    drive_w_PID(forward, 14, inches, 50);
    turn_to_heading(180);
    drive_w_PID(reverse, 24, inches, 50);  
    mogoGODOWN();

    //Rings
    intakeSTART();
    turn_to_heading(90);
    drive_w_PID(forward, 24, inches);
    turn_to_heading(0);
    drive_w_PID(forward, 24, inches);
    turn_to_heading(270);
    drive_w_PID(forward, 24, inches);
    drive_w_PID(forward, 12, inches);
    drive_w_PID(reverse, 36, inches);
    turn_to_heading(305);
    drive_w_PID(forward, 20, inches);
    turn_to_heading(105);
    turn_to_heading(105);
    drive_w_PID(reverse, 16, inches);
    mogoGOUP();
    intakeSTOP();
    Intake.spinFor(reverse, 180, degrees);

    //Reset
    wait(300,msec);
    curveDrive(24, 6, inches, 75, 18.75);
    turn_to_heading(0, 100);
    drive_w_PID(reverse, 74, inches, 80, true);

    //mogo
    mogoGODOWN();
    intakeSTART();
    turn_to_heading(90);
    drive_w_PID(forward, 18, inches);
    turn_to_heading(180);
    drive_w_PID(forward, 24, inches);
    turn_to_heading(270);
    drive_w_PID(forward, 24, inches);
    drive_w_PID(forward, 12, inches);
    drive_w_PID(reverse, 36, inches);
    turn_to_heading(215);
    drive_w_PID(forward, 20, inches);
    turn_to_heading(25);
    drive_w_PID(reverse, 16, inches);
    mogoGOUP();
    intakeSTOP();
    Intake.spinFor(reverse, 180, degrees);







    //Endgame
    Lift.spinToPosition(1700,degrees,false);
    turn_to_heading(45);
    drive_w_PID(forward, 60, inches);
}