#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
using namespace vex;

void autonPlanD()
{
<<<<<<< Updated upstream
    Controller.Screen.print("Plan D");
    mogo.set(true);
    Imu.setHeading(180, degrees);
=======
    // mogo.set(true);
    // Imu.setHeading(180, degrees);
    // pid_Init();
    // driveFor2(reverse, 12, inches, 30);
    // turnToHeading2(267, 20);
    // driveFor2(reverse, 3, inches, 30);
    // Intake.setVelocity(40,percent);
    // Intake.spin(forward);

    // wait(1,sec);
    // Intake.stop();
    // driveFor2(forward, 10, inches);
    // Intake.setVelocity(100,percent);
    // Intake.spin(forward);
    // turnToHeading2(134);
    // driveFor2(reverse, 31.5, inches, 70);
    // mogo.set(false);

    // turnToHeading2(2);
    // driveFor2(forward, 24, inches);
    // turnToHeading2(275);
    // driveFor2(forward, 15, inches);
    // wait(1,sec);
    // turnToHeading2(347);
    // driveFor2(reverse, 35, inches);
    // pid_Ends();

>>>>>>> Stashed changes
    pid_Init();
    mogo.set(true);
    Imu.setHeading(0, degrees);
// ring on alliance stake
    driveFor2(reverse, 14, inches, 30);
    turnToHeading2(270, 20);
    driveFor2(reverse, 6, inches, 25);
    Intake.setVelocity(40,percent);
    Intake.spin(forward);
    driveFor2(forward, 4, inches, 30);
    wait(1, seconds);
    Intake.stop();

    wait(1000,sec);

// mogo collection
    driveFor2(forward, 10, inches, 30);
    Intake.setVelocity(100,percent);
    Intake.spin(forward);
    turnToHeading2(134);
    driveFor2(reverse, 30, inches, 65);
    mogo.set(true);
    wait(0.5, seconds);
    mogo.set(false);
// ring collection

// touch ladder


       




<<<<<<< Updated upstream
    turnToHeading2(359);
    driveFor2(forward, 24, inches);
    turnToHeading2(270);
    driveFor2(forward, 15, inches);
    wait(1,sec);
    turnToHeading2(0);
    driveFor2(reverse, 35, inches);
    pid_Ends();
}
=======
} 
>>>>>>> Stashed changes
