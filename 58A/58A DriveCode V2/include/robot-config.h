#include "vex.h"
#include "vex_imu.h"
#include "vex_triport.h"
using namespace vex;
extern brain Brain;
extern controller Controller;
extern motor L1;
extern motor L2;
extern motor L3;
extern motor R1;
extern motor R2;
extern motor R3;
extern motor LeftLift;
extern motor RightLift;
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;
extern drivetrain Drivetrain;
extern motor Intake;
extern motor_group Lift;
extern inertial Imu;
extern digital_out mogo;

// extern bool connection[];
// extern bool sensors[];

void robot_init(void);
void imu_init(void);

void rampToIntakePos();
void rampToNeutralStake();
void rampToAllianceStake();
void toggleIntakeFwd();
void toggleIntakeRev();
// void selfCheck(void);