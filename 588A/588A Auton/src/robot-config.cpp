#include "../include/vex.h"
#include "vex_controller.h"
#include "vex_drivetrain.h"
#include "vex_global.h"
#include "vex_imu.h"
#include "vex_motor.h"
#include "vex_motorgroup.h"
using namespace vex;
brain Brain;
controller Controller1 = controller(primary);
motor L1 = motor(PORT9, ratio18_1, true);//
motor L2 = motor(PORT19, ratio18_1, true);//
motor L3 = motor(PORT8, ratio18_1, false);//
motor R1 = motor(PORT11, ratio18_1, false);//
motor R2 = motor(PORT14, ratio18_1, false);//
motor R3 = motor(PORT6, ratio18_1, true);//
motor_group RightDrive = motor_group(R1, R2, R3);
motor_group LeftDrive = motor_group(L1, L2, L3);
drivetrain Drivetrain = drivetrain(LeftDrive, RightDrive, 320, 280, 241, mm);
inertial Imu = inertial(PORT18);//
motor PrimaryIntake = motor(PORT21, ratio18_1, false);//
motor_group Intake = motor_group(PrimaryIntake);//
motor mogo = motor(PORT13, ratio18_1, false);//
motor Lift1 = motor(PORT16, ratio36_1, true);//
motor_group Lift = motor_group(Lift1);

void robot_init(void)
{
    LeftDrive.setMaxTorque(100,percent);
    LeftDrive.setStopping(coast);
    RightDrive.setMaxTorque(100,percent);
    RightDrive.setStopping(coast);
    Intake.setMaxTorque(100,percent);
    Intake.setVelocity(100,percent);
    Lift.setMaxTorque(100,percent);
    Lift.setVelocity(50, percent);
    mogo.setMaxTorque(100,percent);
    mogo.setVelocity(100,percent);
    mogo.setStopping(hold);
    printf("robot initialized\n");
}
void imu_init(void)
{
    Brain.Screen.print("Imu initialization...");
    Brain.Screen.setCursor(2, 1);
    // calibrate the drivetrain Inertial
    wait(200, msec);
    Imu.calibrate();
    Brain.Screen.print("Calibrating Inertial for Drivetrain");
    // wait for the Inertial calibration process to finish
    while (Imu.isCalibrating()){
      wait(25, msec);
    }
    // reset the screen now that the calibration is complete
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1,1);
    // Controller1.rumble("..");
    printf("Imu initialized\n");
}
void mogoGOUP()
{
    mogo.spinFor(forward, 360, degrees, false);
}
void mogoGODOWN()
{
    mogo.spin(reverse);
    wait(300,msec);
    while(fabs(mogo.velocity(percent)) > 5)
    {
        wait(10,msec);
    }
    mogo.stop();
}
bool autoIntake = false;
int intakeLoop()
{
    while(autoIntake)
    {
        Intake.spin(forward);
        wait(100,msec);
        if(Intake.velocity(percent) < 10)
        {
            Intake.spinFor(reverse, 360, degrees);
        }
        wait(10,msec);
    }
    return 0;
}

void intakeSTART()
{
    autoIntake = true;
    Intake.spin(forward);
    task intakeLoopTask(intakeLoop);
}
void intakeSTOP()
{
    autoIntake = false;
    Intake.stop();
}