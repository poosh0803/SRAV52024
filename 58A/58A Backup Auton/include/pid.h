void pid_Init();
void pid_Ends();
void turn_w_PID(vex::turnType dir, double target);
void driveFor3(double Ltarget, double Rtarget, vex::distanceUnits units = vex::distanceUnits::mm,double Lspeed = 100, double Rspeed = 100);
void turnToHeading2(double targetHeading, double speed = 60);
void driveFor2(vex::directionType dir, double target, vex::distanceUnits units, double speed = 80);
void drive_for_time(vex::directionType direction, double timeLength);