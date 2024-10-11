/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       maxx                                                      */
/*    Created:      03/03/2024, 13:49:57                                      */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "../include/vex.h"
#include "../include/robot-config.h"
#include "../include/display.h"
// #include "../include/driveCode.h"
#include "../include/preAuton.h"
#include "../include/vision.h"
using namespace vex;
competition Competition;
void autonomous(void)
{
  // autonPlanA();
  // autonPlanB();
  autonSkill();
}

void usercontrol(void)
{
  // controllerReg();
  // while (1) {
  //   wait(20, msec);
  // }
}

int main()
{
  printf("\033[2J");
  robot_init();
  imu_init();
  display_init();
  Competition.autonomous(autonomous);
//   Uncomment to test mogo tracking with vision sensors
//   Competition.autonomous(Vision::testVision);
  Competition.drivercontrol(usercontrol);
  while (true) {
    wait(100, msec);
  }
}