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
<<<<<<< Updated upstream
  // autonPlanA(); //Red Bot Slot 2
  // autonPlanB(); //Red Top Slot 3
=======
  autonPlanA(); //Red Bot Slot 2
  // // autonPlanB(); //Red Top Slot 3
>>>>>>> Stashed changes
  // autonPlanC(); //Blue Bot Slot 4
  autonPlanD(); //Blue Top Slot 5
  // autonSkill();
}

void usercontrol(void)
{
  controllerReg();
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