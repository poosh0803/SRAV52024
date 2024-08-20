#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "../include/pid.h"
using namespace vex;

void autonPlanA()
{
    pid_Init();
<<<<<<< Updated upstream
    drive_w_PID(forward,48,inches,50);
    wait(1,sec);
    drive_w_PID(reverse,48,inches,50);
    turn_w_PID(right, 90);
    wait(0.5,sec);
    turn_w_PID(right, 90);
    wait(0.5,sec);
    turn_w_PID(right, 90);
    wait(0.5,sec);
    turn_w_PID(right, 90);
    wait(0.5,sec);
=======
    
    
>>>>>>> Stashed changes
}