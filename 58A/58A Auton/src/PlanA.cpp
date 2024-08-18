#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
using namespace vex;

void autonPlanA()
{
    pid_Init();
    
    Drivetrain.setDriveVelocity(100,percent);
    Drivetrain.driveFor(forward,48, inches);
    Drivetrain.turnFor(left,90,degrees);
}