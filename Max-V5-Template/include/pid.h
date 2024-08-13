#ifndef F88165DE_9DD8_436A_ACB8_5E124F1A2FFF
#define F88165DE_9DD8_436A_ACB8_5E124F1A2FFF
void pid_Init();
void pid_Ends();
void turn_w_PID(vex::turnType dir, double target);
void turn_to_heading(double targetHeading);
void drive_w_PID(vex::directionType dir, double target, vex::distanceUnits units);


#endif /* F88165DE_9DD8_436A_ACB8_5E124F1A2FFF */
