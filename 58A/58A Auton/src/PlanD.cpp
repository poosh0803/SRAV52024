#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
using namespace vex;

void autonPlanD()
{
    mogo.set(true);
    Imu.setHeading(180, degrees);
    pid_Init();
    driveFor2(reverse, 12, inches, 30);
    turnToHeading2(267, 20);
    driveFor2(reverse, 3, inches, 30);
    Intake.setVelocity(40,percent);
    Intake.spin(forward);

    wait(1,sec);
    Intake.stop();
    driveFor2(forward, 10, inches);
    Intake.setVelocity(100,percent);
    Intake.spin(forward);
    turnToHeading2(134);
    driveFor2(reverse, 31.5, inches, 70);
    mogo.set(false);

    turnToHeading2(2);
    driveFor2(forward, 24, inches);
    turnToHeading2(275);
    driveFor2(forward, 15, inches);
    wait(1,sec);
    turnToHeading2(347);
    driveFor2(reverse, 35, inches);
    pid_Ends();
} 
