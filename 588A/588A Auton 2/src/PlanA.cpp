#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "vex_units.h"
#include "../include/vision.h"
using namespace vex;

void autonPlanA() {
    Imu.setHeading(0, degrees);
    pid_Init();
    mogoGOUP();

    drive_w_PID(reverse, 100, inches, 80, true);
    mogoGODOWN();
}