void pid_Init();
void pid_Ends();
void turn_w_PID(vex::turnType dir, double target);

void turnToHeading2(double targetHeading, double speed = 80);
void driveFor2(vex::directionType dir, double target, vex::distanceUnits units, double speed=80);
void drive_for_time(vex::directionType direction, double timeLength);
void mogoCorrection(bool direction, int limit);
double getTravelDist();
bool isMogo();