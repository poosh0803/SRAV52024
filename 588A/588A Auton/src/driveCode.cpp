#include "../include/vex.h"
#include "../include/robot-config.h"
#include "../include/drive-assist.h"
#include "vex_global.h"
#include "vex_motorgroup.h"
#include "vex_units.h"
#include <cstdio>
using namespace vex;
int armANDshooter = 0;
bool shifting = false;
bool wallOut = false;
bool intaking;

void shoot()
{
  if(armANDshooter == 1)
  {
    ShooterArm.spinFor(forward, 360, degrees);
  }
}
void intakeUP()
{
  if(intaking)
  {
    intaking = false;
    Intake.stop();
  }
  else
  {
    intaking = true;
    Intake.spin(forward);
  }
}
void intakeDOWN()
{
  Intake.setVelocity(100,percent);
  Intake.spin(reverse);
}
void intakeNone()
{
  if(intaking)
  {
    Intake.spin(forward);
  }
  else
  {
    Intake.stop();
  }
}
double toTemp = 0;
void brakeTriggerOn()
{
  Controller1.rumble(".");
  Drivetrain.setStopping(brake);
  Drivetrain.setDriveVelocity(0, percent);
  toTemp = maxDriveSpeed;
  maxDriveSpeed = 0;
  wait(1000,msec);
  if(Controller1.ButtonR2.pressing())
  {
    Drivetrain.setStopping(hold);
  }
}
void brakeTriggerOff()
{
  maxDriveSpeed = toTemp;
  Drivetrain.setStopping(coast);
  Drivetrain.setDriveVelocity(maxDriveSpeed, percent);
}
void shooterArmUp()
{
  ShooterArm.spin(forward);
}
void shooterArmDown()
{
  if(armANDshooter == 1) {return;}
  ShooterArm.spin(reverse);
}
void shooterArmNone()
{
  ShooterArm.stop();
}
void switchFacing()
{
  Controller1.Screen.setCursor(2, 1);
  if(facingBack)
  {
    facingBack = false;
    Controller1.rumble(".");
    Controller1.Screen.print("Front: Flat             ");
  }
  else
  {
    facingBack = true;
    Controller1.rumble("..");
    Controller1.Screen.print("Front: Intake          ");
  }
}
void wallExpand()
{
  if(wallOut)
  {
    wallOut = false;
    wallEX.set(false);
    Controller1.rumble(".");
  }
  else
  {
    wallOut = true;
    wallEX.set(true);
    Controller1.rumble("..");
  }
}
int hangSafeLock = 1;
void endGameHang()
{
  if(hangSafeLock > 0)
  {
    hangSafeLock--;
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("END: ");
    for(int i = 0; i<hangSafeLock;i++)
    {
      Controller1.Screen.print("X ");
    }
    Controller1.Screen.print("              ");
    Controller1.rumble(".");
    return;
  }
  hangLock = true;
  Controller1.rumble("...");
  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.print("END: LOCKED         ");
}
void gearBoxSwitch()
{
  if(shifting) {return;}
  shifting = true;
  ShooterArm.setBrake(coast);
  wait(100,msec);
  if(armANDshooter == 0)
  {
    armANDshooter = 1;
    shooterShift = true;
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Gear: Shooter        ");
  }
  else
  {
    armANDshooter = 0;
    wait(300,msec);
    bigArmShift = true;
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print("Gear: BigArm        ");
  }

  wait(100,msec);
  ShooterArm.setVelocity(10,percent);
  ShooterArm.setMaxTorque(100,percent);
  ShooterArm.spinFor(10,degrees,true);
  // wait(100,msec);
  ShooterArm.spinFor(-10,degrees,true);
  // wait(100,msec);
  ShooterArm.setVelocity(100,percent);
  ShooterArm.setMaxTorque(100,percent);
  ShooterArm.setBrake(hold);
  shifting = false;
  bigArmShift = false;
  shooterShift = false;
}
int rapidLock = 1;
void rapidShoot()
{
  if(armANDshooter == 0) {return;}
  if(rapidLock > 0)
  {
    rapidLock--;
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("Rapid: ");
    for(int i = 0; i<rapidLock;i++)
    {
      Controller1.Screen.print("X ");
    }
    Controller1.Screen.print("              ");
    Controller1.rumble(".");
    return;
  }
  ShooterArm.setMaxTorque(100,percent);
  ShooterArm.setVelocity(100,percent);
  int rep = 0;
  while(rep < 45)
  {
    if(rep>=40)
    {
      Controller1.rumble(".");
    }
    ShooterArm.spinFor(forward, 360,degrees, false);
    rep++;
    printf("rep: %d", rep);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print("Rapid: %d              ", 45-rep);
    wait(750,msec);
  }
}
void controllerReg()
{
  Controller1.ButtonUp.pressed(shoot);
  Controller1.ButtonRight.pressed(endGameHang);
  Controller1.ButtonLeft.pressed(gearBoxSwitch);
  Controller1.ButtonDown.pressed(rapidShoot);
  Controller1.ButtonR1.pressed(wallExpand);
  Controller1.ButtonL1.pressed(intakeUP);
  Controller1.ButtonL2.pressed(intakeDOWN);
  Controller1.ButtonL2.released(intakeNone);
  Controller1.ButtonX.pressed(switchFacing);
  Controller1.ButtonR2.pressed(brakeTriggerOn);
  Controller1.ButtonR2.released(brakeTriggerOff);
  Controller1.ButtonY.pressed(shooterArmUp);
  Controller1.ButtonY.released(shooterArmNone);
  Controller1.ButtonB.pressed(shooterArmDown);
  Controller1.ButtonB.released(shooterArmNone);
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Gear: BigArm            ");
  Controller1.Screen.setCursor(2, 1);
  Controller1.Screen.print("Front: Flat             ");
  Controller1.Screen.setCursor(3, 1);
  Controller1.Screen.print("Rapid: X                ");
}