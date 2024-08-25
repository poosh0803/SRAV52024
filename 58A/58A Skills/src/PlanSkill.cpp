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
    // Stage2();

    pid_Ends();
}

void Stage1()
{
    //Goal 1
    driveFor2(reverse, 5, inches, 100);
    // wait(0.5, sec);
    mogo.set(false);
    rollerStart();

    //Ring 2
    wait(0.2, sec);
    turnToHeading2(90, 80);
    wait(0.1, sec);
    driveFor2(fwd, 29, inches, 80);

    //Ring 3
    turnToHeading2(180);
    wait(0.1, sec);
    driveFor2(fwd, 24, inches, 80);

    //Ring 4,5
    turnToHeading2(270);
    wait(0.1, sec);
    driveFor2(fwd, 18, inches, 50);
    turnToHeading2(270);
    driveFor2(fwd, 10, inches, 40);
    wait(0.1, sec);

    //Ring 6
    driveFor2(reverse, 24, inches, 80);
    turnToHeading2(215);
    wait(0.1, sec);
    driveFor2(fwd, 20, inches, 80);

    //Scoring the goal
    turnToHeading2(45);
    wait(0.1, sec);
    driveFor2(reverse, 10, inches, 80);
    mogo.set(true);
    rollerEnd();
}

void Stage2()
{
    //Transtion from Stage
    driveFor2(forward, 4, inches, 80);
    turnToHeading2(0);
    wait(0.1, sec);
    driveFor2(reverse, 72, inches, 80);
    mogo.set(false);
    driveFor2(reverse, 2, inches, 80);
    rollerStart();

    //Ring 1
    turnToHeading2(90);
    wait(0.1, sec);
    driveFor2(fwd, 28, inches, 80);
    
    //Ring 2
    turnToHeading2(0);
    wait(0.1, sec);
    driveFor2(fwd, 28, inches, 80);

    //Ring 3,4
    turnToHeading2(270);
    wait(0.1, sec);
    driveFor2(fwd, 36, inches, 80);
    wait(0.1, sec);

    //Ring 5
    driveFor2(reverse, 24, inches, 80);
    turnToHeading2(45);
    wait(0.1, sec);
    driveFor2(fwd, 20, inches, 80);
    rollerEnd();

    //Scoring the goal
    turnToHeading2(135);
    wait(0.1, sec);
    driveFor2(reverse, 24, inches, 80);
    mogo.set(true);

}