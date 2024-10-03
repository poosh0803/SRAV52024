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
#include "../include/driveCode.h"
using namespace vex;
competition Competition;
void autonomous(void)
{
  // autonPlanA();
  // autonPlanB();
  // autonPlanC();
  // autonPlanD();
  //autonSkill();
}
void usercontrol(void)
{
  driveCode_Init();
  while (1) {
    wait(20, msec);
  }
}
int main()
{
  robot_init();
  imu_init();
  display_init();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  while (true) {
    wait(100, msec);
  }
}