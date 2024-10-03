#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"

using namespace vex;

// Intake Setup
bool roller = false;
int IntakeLoop()
{
    Intake.spin(forward);
    wait(500, msec);
    while (roller)
    {
        if (fabs(Intake.velocity(vex::velocityUnits::pct)) < 6)
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

// Mogo Setup
bool clampingAuton = false;

void clampToggleAuton()
{
  if(clampingAuton) {
    clampingAuton = false;
    mogo.set(false);
  } 
  else {
    clampingAuton = true;
    mogo.set(true);
  }
}

// Mogo Optical Sensor
bool isMogo()
{
  bool result = (mogoSensor.hue() > 60 && mogoSensor.hue() < 70);
  // if(result) {
  //   printf("Mogo Detected\n");    
  // }
  // else {
  //   printf("\n");
  // }
  return result;
}

// Mogo Detection
double travelDist = 0;

void mogoCorrection(bool direction, int limit)
{
  while(isMogo() == false && travelDist + 1 <= limit) {
    if (direction == true) {
      driveFor2(forward, 1, inches, 70);
      travelDist += 1;
    }
    else {
      driveFor2(reverse, 1, inches, 70);
      travelDist += 1;
    }
  }
}

double getTravelDist()
{
  return travelDist;
}