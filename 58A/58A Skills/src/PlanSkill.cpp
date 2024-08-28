#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"

using namespace vex;

bool roller = false;
int IntakeLoop()
{
    Intake.spin(forward);
    wait(500, msec);
    while (roller)
    {
        if (fabs(Intake.velocity(vex::velocityUnits::pct) < 6))
        {
            Intake.spin(reverse);
            wait(200, msec);
            Intake.spin(forward);
            wait(200, msec);
        }
        wait(100, msec);
    }
    return 0;
}

void rollerStart()
{
    roller = true;
    vex::task StartIntake(IntakeLoop);
}

void rollerEnd()
{
    roller = false;
    Intake.stop();
}

void autonSkill()
{
    pid_Init();
    mogo.set(true);
    Imu.setHeading(270,degrees);
    Stage1();
    Stage3();
    // Stage2();

    pid_Ends();
}

void Stage1()
{
    //Goal 1
    driveFor2(reverse, 5, inches, 50);
    // wait(0.5, sec);
    mogo.set(false);
    rollerStart();

    //Ring 2
    wait(0.2, sec);
    turnToHeading2(90);
    wait(0.1, sec);
    driveFor2(fwd, 29, inches, 70);

    //Ring 3
    turnToHeading2(180);
    wait(0.1, sec);
    driveFor2(fwd, 25, inches, 70);

    //Ring 4,5
    turnToHeading2(270);
    wait(0.1, sec);
    driveFor2(fwd, 18, inches, 50);
    turnToHeading2(270);
    driveFor2(fwd, 10, inches, 40);
    wait(0.1, sec);

    //Ring 6
    turnToHeading2(135);
    wait(0.1, sec);
    driveFor3(17, 34, inches, 30, 60);
    // driveFor2(fwd, 20, inches, 70);


    Intake.spinFor(reverse, 200, degrees);
    // wait(1000,sec);
    //Scoring the goal
    // turnToHeading2(45, 80);
    // wait(0.2, sec);
    driveFor2(reverse, 22, inches, 70);
    mogo.set(true);
    turnToHeading2(68);
    rollerEnd();
}

void Stage2()
{
    //Transtion Goal 1 - Goal 2
    driveFor2(fwd, 10, inches, 70);
    turnToHeading2(180, 70);
    wait(0.1, sec);
    driveFor2(reverse, 32, inches, 70);
    mogo.set(false);

    rollerStart();
    wait(0.1, sec);

    //Ring 2
    turnToHeading2(90, 70);
    wait(0.1, sec);
    driveFor2(fwd, 25, inches, 70);

    //Ring 3
    turnToHeading2(180);
    wait(0.1, sec);
    driveFor2(fwd, 25, inches, 70);

    //Ring 4,5
    turnToHeading2(270);
    wait(0.1, sec);
    driveFor2(fwd, 18, inches, 70);
    turnToHeading2(270);
    driveFor2(fwd, 10, inches, 40);
    wait(0.1, sec);

    //Ring 6
    turnToHeading2(135);
    wait(0.1, sec);
    // driveFor3(20, 40, inches, 30, 60);
    driveFor2(fwd, 10, inches, 70);


    //Scoring the goal
    turnToHeading2(45, 80);
    wait(0.2, sec);
    driveFor2(reverse, 20, inches, 80);
    mogo.set(true);
    rollerEnd();

}

void Stage3()
{
    driveFor2(fwd, 10, inches, 70);
    turnToHeading2(180, 70);
    wait(0.1, sec);
    driveFor2(reverse, 32, inches, 70);
    mogo.set(false);
    turnToHeading2(135, 70);
    wait(0.1, sec);
    driveFor2(reverse, 15, inches, 70);

    driveFor2(reverse, 96, inches, 70);
    turnToHeading2(45, 70);

}