#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
using namespace vex;

void autonSkill()
{
    pid_Init();
    mogo.set(true);
    Imu.setHeading(270,degrees);
    Stage1();

    pid_Ends();
}

void Stage1()
{
    //Goal 1
    driveFor2(reverse, 5, inches, 100);
    wait(0.5, sec);
    mogo.set(false);
    Intake.spin(forward);

    //Ring 2
    turnToHeading2(90);
    wait(0.1, sec);
    driveFor2(fwd, 28, inches, 100);

    //Ring 3
    turnToHeading2(180);
    wait(0.1, sec);
    driveFor2(fwd, 24, inches, 100);

    //Ring 4,5
    turnToHeading2(270);
    wait(0.1, sec);
    driveFor2(fwd, 24, inches, 100);
    wait(0.5, sec);
    driveFor2(fwd, 24, inches, 100);
    wait(0.5, sec);

    //Ring 6
    driveFor2(reverse, 24, inches, 100);
    turnToHeading2(135);
    wait(0.1, sec);
    driveFor2(fwd, 20, inches, 100);
    Intake.stop();

    //Scoring the goal
    turnToHeading2(45);
    wait(0.1, sec);
    driveFor2(reverse, 24, inches, 100);
    mogo.set(true);

}

void Stage2()
{
    //Goal 1
    driveFor2(reverse, 5, inches, 100);
    wait(0.5, sec);
    mogo.set(false);
    Intake.spin(forward);

    //Ring 1
    turnToHeading2(90);
    wait(0.1, sec);
    driveFor2(fwd, 28, inches, 100);
    
    //Ring 2
    turnToHeading2(0);
    wait(0.1, sec);
    driveFor2(fwd, 28, inches, 100);

    //Ring 3,4
    turnToHeading2(270);
    wait(0.1, sec);
    driveFor2(fwd, 36, inches, 100);
    wait(0.1, sec);

    //Ring 5
    driveFor2(reverse, 24, inches, 100);
    turnToHeading2(45);
    wait(0.1, sec);
    driveFor2(fwd, 20, inches, 100);
    Intake.stop();

    //Scoring the goal
    turnToHeading2(135);
    wait(0.1, sec);
    driveFor2(reverse, 24, inches, 100);
    mogo.set(true);

}

