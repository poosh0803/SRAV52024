#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
#include "vex_units.h"
using namespace vex;

void autonPlanA()
{
    pid_Init();
    
    drive_w_PID(forward,48,inches);
    wait(1,sec);
    drive_w_PID(reverse,48,inches);
    turn_w_PID(right, 90);
    wait(500,msec);
    turn_w_PID(right, 90);
    wait(500,msec);
    turn_w_PID(right, 90);
    wait(500,msec);
    turn_w_PID(right, 90);
    wait(500,msec);

    pid_Ends();
}