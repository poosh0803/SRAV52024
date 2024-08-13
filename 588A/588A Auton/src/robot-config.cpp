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
motor L1 = motor(PORT19, ratio6_1, true);
motor L2 = motor(PORT20, ratio6_1, false);
motor L3 = motor(PORT18, ratio6_1, true);
motor R1 = motor(PORT15, ratio6_1, false);
motor R2 = motor(PORT16, ratio6_1, true);
motor R3 = motor(PORT14, ratio6_1, false);
motor_group RightDrive = motor_group(R1, R2, R3);
motor_group LeftDrive = motor_group(L1, L2, L3);
drivetrain Drivetrain = drivetrain(LeftDrive, RightDrive, 320, 280, 241, mm, 48.0/84.0);
inertial Imu = inertial(PORT1);
motor PrimaryIntake = motor(PORT3, ratio18_1, true);
motor SecondIntake = motor(PORT4, ratio18_1, true);
motor_group Intake = motor_group(PrimaryIntake, SecondIntake);
motor Lift = motor(PORT17, ratio18_1, true);
digital_out mogo = digital_out(Brain.ThreeWirePort.A);

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

// bool connection[] = {false, false, false, false, false, false, false, false}; //9
// bool sensors[] = {false, false, false}; //Inertial, Resetter, Controller
// void selfCheck()
// {
//   motor motors[] = {L1, L2, L3, R1, R2, R3, ShooterArm, Intake};
//   for(int i=0; i<8; i++)
//   {
//     if(motors[i].installed())
//     {
//       connection[i] = true;
//     }
//   }
//   if(Imu.installed())
//   {
//     sensors[0] = true;
//   }
//   if(ballDetecter.installed())
//   {
//     sensors[1] = true;
//     ballDetecterEnabled = true;
//   }
//   if(Controller1.installed())
//   {
//     sensors[2] = true;
//   }
// }