#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "../include/preAuton.h"

using namespace vex;

void autonSkill()
{
    pid_Init();
    mogo.set(true);
    Imu.setHeading(90, degrees);
    
    Stage0();
    Stage1();
    Stage2();

    pid_Ends();
}

void Stage0()
{
    //Alliance Wall Stake
    rollerStart();
    wait(1, sec);
    rollerEnd();
    driveFor2(forward, 12, inches, 70);
    turnToHeading2(0);
    driveFor2(reverse, 20, inches, 50);
    mogoCorrection(false, 4);

}
void Stage1()
{
    //Goal 1
    // driveFor2(reverse, 5, inches, 45);
    // mogoCorrection(false, 29);
    // wait(0.5, sec);
    mogo.set(false);
    driveFor2(reverse, 3, inches, 45);
    rollerStart();

    //Ring 2
    wait(0.2, sec);
    turnToHeading2(90);
    wait(0.1, sec);
    driveFor2(fwd, 24, inches, 71);

    //Ring 3
    turnToHeading2(180);
    wait(0.1, sec);
    driveFor2(fwd, 25, inches, 71);

    //Ring 4,5
    turnToHeading2(270);
    wait(0.1, sec);
    driveFor2(fwd, 18, inches, 51);
    turnToHeading2(270);
    driveFor2(fwd, 12, inches, 43);
    wait(0.1, sec);

    //Ring 6
    turnToHeading2(135);
    wait(0.1, sec);
    driveFor3(17, 34, inches, 30, 60);

    // driveFor2(fwd, 20, inches, 70);
    // wait(1000,sec);
    //Scoring the goal
    // turnToHeading2(45, 80);
    // wait(0.2, sec);
    driveFor2(reverse, 24, inches, 71);
    mogo.set(true);
    // turnToHeading2(68);
    rollerEnd();
}

void Stage2()
{
    //Transtion Goal 1 - Goal 2
    driveFor2(fwd, 3, inches, 71);
    turnToHeading2(180, 70);
    wait(0.1, sec);
    driveFor2(reverse, 36, inches, 71);
    turnToHeading2(180, 70);
    driveFor2(reverse, 36, inches, 71);
    mogoCorrection();
    mogo.set(false);

    rollerStart();
    wait(0.1, sec);

    //Ring 2
    turnToHeading2(90, 70);
    wait(0.1, sec);
    driveFor2(fwd, 25, inches, 71);

    //Ring 3
    turnToHeading2(180);
    wait(0.1, sec);
    driveFor2(fwd, 25, inches, 71);

    //Ring 4,5
    turnToHeading2(270);
    wait(0.1, sec);
    driveFor2(fwd, 18, inches, 71);
    turnToHeading2(270);
    driveFor2(fwd, 10, inches, 41);
    wait(0.1, sec);

    //Ring 6
    turnToHeading2(135);
    wait(0.1, sec);
    // driveFor3(20, 40, inches, 30, 60);
    driveFor2(fwd, 10, inches, 71);


    //Scoring the goal
    turnToHeading2(45, 80);
    wait(0.2, sec);
    driveFor2(reverse, 20, inches, 81);
    mogo.set(true);
    rollerEnd();

}
