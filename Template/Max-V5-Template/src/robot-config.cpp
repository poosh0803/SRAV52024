#include "../include/vex.h"
#include "vex_controller.h"
#include "vex_drivetrain.h"
#include "vex_global.h"
#include "vex_imu.h"
#include "vex_motor.h"
#include "vex_motorgroup.h"
#include "../include/drive-assist.h"
using namespace vex;
brain Brain;
controller Controller1 = controller(primary);

motor R1 = motor(PORT17, ratio6_1, false);
motor R2 = motor(PORT18, ratio6_1, true);
motor R3 = motor(PORT9, ratio6_1, true);
motor L1 = motor(PORT11, ratio6_1, true);
motor L2 = motor(PORT5, ratio6_1, false);
motor L3 = motor(PORT14, ratio6_1, false);
motor_group RightDrive = motor_group(R1, R2, R3);
motor_group LeftDrive = motor_group(L1, L2, L3);
drivetrain Drivetrain = drivetrain(LeftDrive, RightDrive, 320, 280, 241, mm, 48.0/84.0);
inertial Imu = inertial(PORT1);

motor ShooterArm = motor(PORT10, ratio36_1, false);
motor Intake = motor(PORT21, ratio18_1, false);

distance ballDetecter = distance(PORT3);
digital_out hangLock = digital_out(Brain.ThreeWirePort.E);
digital_out wallEX = digital_out(Brain.ThreeWirePort.F);
digital_out bigArmShift = digital_out(Brain.ThreeWirePort.H);
digital_out shooterShift = digital_out(Brain.ThreeWirePort.G);

bool connection[] = {false, false, false, false, false, false, false, false}; //9
bool sensors[] = {false, false, false}; //Inertial, Resetter, Controller
void selfCheck()
{
  motor motors[] = {L1, L2, L3, R1, R2, R3, ShooterArm, Intake};
  for(int i=0; i<8; i++)
  {
    if(motors[i].installed())
    {
      connection[i] = true;
    }
  }
  if(Imu.installed())
  {
    sensors[0] = true;
  }
  if(ballDetecter.installed())
  {
    sensors[1] = true;
    ballDetecterEnabled = true;
  }
  if(Controller1.installed())
  {
    sensors[2] = true;
  }
}
void robot_init(void)
{
    LeftDrive.setMaxTorque(100,percent);
    LeftDrive.setStopping(coast);
    RightDrive.setMaxTorque(100,percent);
    RightDrive.setStopping(coast);
    ShooterArm.setMaxTorque(100,percent);
    ShooterArm.setVelocity(100,percent);
    ShooterArm.setStopping(hold);
    Intake.setMaxTorque(100,percent);
    Intake.setVelocity(100,percent);
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