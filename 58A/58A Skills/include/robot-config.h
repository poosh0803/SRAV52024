#include "vex.h"
#include "vex_imu.h"
#include "vex_triport.h"

#define GREEN   "\x1B[32m"
#define RED     "\x1B[31m"
#define NORM    "\x1B[0m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"

#define MGTA_BG "\x1B[105m"             // Magenta background

#define ERROR   "\x1B[30;101;1;4m"      // Bold white text on red background with underline
#define WARN    "\x1B[33;1;4m"          // Bold yellow text on red background with underline
#define INFO    "\x1B[34;1;4m"          // Bold blue text on normal background with underline
#define DEBUG   "\x1B[32;1;4m"          // Bold green text on normal background with underline

using namespace vex;
extern brain Brain;
extern controller Controller;
extern motor L1;
extern motor L2;
extern motor L3;
extern motor R1;
extern motor R2;
extern motor R3;
extern motor_group LeftDriveSmart;
extern motor_group RightDriveSmart;
extern drivetrain Drivetrain;
extern motor primaryIntake;
extern motor secondIntake;
extern motor_group Intake;
extern motor Lift;
extern inertial Imu;
extern digital_out mogo;
extern optical mogoSensor;

extern vision::signature mogoStarboardCam__MOGO;
extern vision mogoStarboardCam;

extern vision::signature mogoPortCam__MOGO;
extern vision mogoPortCam;

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