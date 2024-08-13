#include "vex.h"
#include "vex_imu.h"
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
extern motor Intake;
extern motor ShooterArm;
extern drivetrain Drivetrain;
extern inertial Imu;
extern distance ballDetecter;
extern digital_out hangLock;
extern digital_out wallEX;
extern digital_out bigArmShift;
extern digital_out shooterShift;
extern bool connection[];
extern bool sensors[];
void robot_init(void);
void imu_init(void);
void selfCheck(void);