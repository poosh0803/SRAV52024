#include "vex.h"
#include "vex_imu.h"
#include "vex_triport.h"
using namespace vex;
extern brain Brain;
extern controller Controller1;
extern motor L1;
extern motor L2;
extern motor L3;
extern motor R1;
extern motor R2;
extern motor R3;
extern motor_group LeftDrive;
extern motor_group RightDrive;
extern drivetrain Drivetrain;
extern motor Intake;
extern motor Lift;
extern inertial Imu;
extern digital_out mogo;
// extern bool connection[];
// extern bool sensors[];
void robot_init(void);
void imu_init(void);
// void selfCheck(void);