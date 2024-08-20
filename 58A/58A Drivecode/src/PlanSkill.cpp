#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
using namespace vex;

void autonSkill()
{
    pid_Init();
    mogo.set(true);
    Stage1();
}

void Stage1()
{
    //Goal 1
    Intake.spin(forward);
    driveFor2(reverse, 5, inches, 100);
    wait(0.5, sec);
    mogo.set(false);

    //Ring 2
    turnToHeading2(180);
    wait(0.1, sec);
    driveFor2(fwd, 28, inches, 100);
    
    //Ring 3
    turnToHeading2(270);
    wait(0.1, sec);
    driveFor2(fwd, 28, inches, 100);

    //Ring 4,5
    turnToHeading2(0);
    wait(0.1, sec);
    driveFor2(fwd, 36, inches, 100);
    wait(0.1, sec);

    //Ring 6
    driveFor2(reverse, 24, inches, 100);
    turnToHeading2(315);
    wait(0.1, sec);
    driveFor2(fwd, 20, inches, 100);
    Intake.stop();

    //Scoring the goal
    turnToHeading2(135);
    wait(0.1, sec);
    driveFor2(reverse, 24, inches, 100);
    mogo.set(true);

}