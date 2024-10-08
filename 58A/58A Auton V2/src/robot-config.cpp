#include "../include/vex.h"
#include "vex_controller.h"
#include "vex_drivetrain.h"
#include "vex_global.h"
#include "vex_imu.h"
#include "vex_motor.h"
#include "vex_motorgroup.h"
using namespace vex;
brain Brain;
controller Controller = controller(primary);
motor L1 = motor(PORT5, ratio6_1, false);
motor L2 = motor(PORT6, ratio6_1, true);
motor L3 = motor(PORT7, ratio6_1, true);
motor R1 = motor(PORT9, ratio6_1, true);
motor R2 = motor(PORT10, ratio6_1, false);
motor R3 = motor(PORT8, ratio6_1, false);

motor_group LeftDriveSmart = motor_group(L1, L2, L3);
motor_group RightDriveSmart = motor_group(R1, R2, R3);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 320, 280, 241, mm, 48.0/84.0);

inertial Imu = inertial(PORT16);

motor Intake = motor(PORT1, ratio6_1, true);

motor LeftLift = motor(PORT18, ratio18_1, true);
motor RightLift = motor(PORT17, ratio18_1, false);
motor_group Lift = motor_group(LeftLift, RightLift);

digital_out mogo = digital_out(Brain.ThreeWirePort.A);
optical mogoSensor = optical(PORT19);

void robot_init(void)
{
    LeftDriveSmart.setMaxTorque(100,percent);
    LeftDriveSmart.setStopping(hold);

    RightDriveSmart.setMaxTorque(100,percent);
    RightDriveSmart.setStopping(hold);

    Intake.setMaxTorque(100,percent);
    Intake.setVelocity(100,percent);
    Intake.setStopping(coast);

    Lift.setMaxTorque(100,percent);
    Lift.setVelocity(80, percent);
    Lift.setStopping(hold);
    Lift.setPosition(0, degrees);
    
    mogoSensor.setLightPower(100);

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