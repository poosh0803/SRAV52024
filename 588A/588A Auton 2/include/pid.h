extern double staleTime;
extern double center;
extern double visionKP;

void pid_Init();
void pid_Ends();
void turn_w_PID(vex::turnType dir, double target);
void turn_to_heading(double targetHeading, double speed = 30);
void drive_w_PID(vex::directionType dir, double target, vex::distanceUnits units, double speed = 70, bool trackingMogo = false);
void drive_for_time(vex::directionType direction, double timeLength);
void setMotorPos(double Left, double Right);