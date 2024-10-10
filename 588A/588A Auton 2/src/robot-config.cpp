#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_controller.h"
#include "vex_drivetrain.h"
#include "vex_global.h"
#include "vex_imu.h"
#include "vex_motor.h"
#include "vex_motorgroup.h"
#include "vex_triport.h"

using namespace vex;

brain Brain;
controller Controller1 = controller(primary);

motor L1 = motor(PORT9, ratio18_1, true);//
motor L2 = motor(PORT5, ratio18_1, true);//
motor L3 = motor(PORT2, ratio18_1, false);//
motor R1 = motor(PORT16, ratio18_1, false);//
motor R2 = motor(PORT6, ratio18_1, true);//
motor R3 = motor(PORT7, ratio18_1, false);//
motor_group RightDrive = motor_group(R1, R2, R3);
motor_group LeftDrive = motor_group(L1, L2, L3);
drivetrain Drivetrain = drivetrain(LeftDrive, RightDrive, 320, 280, 241, mm);

inertial Imu = inertial(PORT13);//

motor PrimaryIntake = motor(PORT15, ratio18_1, false);//
motor_group Intake = motor_group(PrimaryIntake);//

motor Lift1 = motor(PORT11, ratio36_1, true);//
motor Lift2 = motor(PORT17, ratio36_1, false);//
motor_group Lift = motor_group(Lift1, Lift2);//

digital_out trapDoor = digital_out(Brain.ThreeWirePort.G);
digital_out Clamp = digital_out(Brain.ThreeWirePort.H);

vision::signature mogoStarboardCam__MOGO = vision::signature(1, -2769, -1219, -1994, -7117, -5391, -6254, 2.900, 0);
vex::vision mogoStarboardCam = vision( vex::PORT3, 26, mogoStarboardCam__MOGO);

vision::signature mogoPortCam__MOGO = vision::signature(1, -2367, -1217, -1792, -6869, -5247, -6058, 4.8, 0);
vex::vision mogoPortCam = vision(PORT4, 50, mogoPortCam__MOGO);

void robot_init(void)
{
    LeftDrive.setMaxTorque(100,percent);
    LeftDrive.setStopping(coast);
    RightDrive.setMaxTorque(100,percent);
    RightDrive.setStopping(coast);
    Intake.setMaxTorque(100,percent);
    Intake.setVelocity(100,percent);
    Lift.setMaxTorque(100,percent);
    Lift.setVelocity(100, percent);
    Lift.setPosition(0, degrees);
    printf("%srobot initialized%s\n", MGTA_BG, NORM);
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
    printf("%sImu initialized%s\n", MGTA_BG, NORM);
}
void mogoGOUP()
{
    Clamp.set(true);
}
void mogoGODOWN()
{
    Clamp.set(false);
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