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
#include "../include/vision.h"
using namespace vex;
competition Competition;
char planSel = 'X';
void usercontrol(void)
{
  driveCode_Init();
  while (1) {
    wait(20, msec);
  }
}
int main()
{
  printf("\033[2J");
   Competition.autonomous(autonPlanA); planSel = 'A'; // Slot 1
  // Competition.autonomous(autonPlanB); planSel = 'B'; // Slot 2
  // Competition.autonomous(autonPlanC); planSel = 'C'; // Slot 3
  // Competition.autonomous(autonPlanD); planSel = 'D'; // Slot 4
  // Competition.autonomous(autonSkill); planSel = 'S'; // Slot 8
  Competition.drivercontrol(usercontrol);
  Controller1.Screen.setCursor(3,1);
  Controller1.Screen.print("Plan %c", planSel);
  robot_init();
  imu_init();
  display_init();
  while (true) {
    wait(100, msec);
  }
}