#include "../include/vex.h"
#include "../include/robot-config.h"
bool driverControl = false;
bool ballDetecterEnabled = false;
bool smoothEnabled = true;
bool throttleEnabled = true;
bool wheelieControlEnabled = false;
bool RemoteControlCodeEnabled = true;
bool facingBack = false;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;
double deadZone = 2;
double inputCurve = 3; //modify this value to change the power of the smoothing from 2-5
double maxDriveSpeed = 100;
double throttle(double inputVelocity, double currentVelocity)
{
    if(!throttleEnabled){return inputVelocity;}
    double kP;
    if((inputVelocity > 0 && currentVelocity < 0) || (inputVelocity < 0 && currentVelocity > 0))
    {
        kP = 0;
    }
    else
    {
        kP = fabs(currentVelocity);
    }
    double result = inputVelocity * kP;
    if(inputVelocity > 0)
    {
        result += 15;
    }
    else if(inputVelocity < 0)
    {
        result -= 15;
    }
    return result;
}
double smoothIt(int inputVelocity, double currentVelocity)
{
    if(!smoothEnabled) {return inputVelocity;}
    double to2 = 100;
    double out = pow(inputVelocity / to2, inputCurve) * maxDriveSpeed;
    if(inputVelocity < 0 && out > 0){out = -out;}
    return throttle(out, currentVelocity);
}
int triballDetectLoop()
{
    while(true)
    {
        if(driverControl&&ballDetecterEnabled)
        {
            if(ballDetecter.objectDistance(mm) < 100 && !Controller1.ButtonL2.pressing())
            {
                Intake.setVelocity(30,percent);
                Intake.setMaxTorque(50, percent);
            }
            else if(Controller1.ButtonL2.pressing())
            {
                Intake.setVelocity(-100,percent);
                Intake.setMaxTorque(100, percent);
            }
            else
            {
                Intake.setVelocity(100,percent);
                Intake.setMaxTorque(100, percent);
            }
        }
        wait(20,msec);
    }
}
int tourqueControl()
{
    double Imu_roll_threashold = 15;
    double Imu_acc_threashold = 0.4;
    double wheelieAngle;
    double accleration;
    double compare;
    int joyStick_threashold = 50;
    int overwrite_countdown = 0;
    while (wheelieControlEnabled)
    {
        wheelieAngle = Imu.roll();
        accleration = Imu.acceleration(yaxis);
        compare = ((Controller1.Axis2.position() + Controller1.Axis3.position()) / 2.0) + Drivetrain.velocity(percent);
        if(fabs(compare) < joyStick_threashold || overwrite_countdown > 0)
        {
            if (fabs(wheelieAngle) > Imu_roll_threashold && (fabs(accleration) > Imu_acc_threashold))
            {
                printf("Wheelie Detected\n");
                LeftDrive.setMaxTorque(20,percent);
                RightDrive.setMaxTorque(20, percent);
                if(overwrite_countdown == 0)
                {
                    overwrite_countdown = 10;
                }
                else
                {
                    overwrite_countdown--;
                }
            }
            else
            {
                LeftDrive.setMaxTorque(100,percent);
                RightDrive.setMaxTorque(100,percent);
            }
        }
        wait(10, msec);
    }
    return 0;
}
int tourqueControlRaw()
{
    double Imu_roll_threashold = 13;
    double Imu_acc_threashold = 0.7;
    double wheelieAngle;
    double accleration;
    int overwrite_countdown = 0;
    while (wheelieControlEnabled)
    {
        wheelieAngle = Imu.roll();
        accleration = Imu.acceleration(yaxis);
            if ((fabs(wheelieAngle) > Imu_roll_threashold && (fabs(accleration) > Imu_acc_threashold)) || overwrite_countdown > 0)
            {
                printf("Wheelie Detected\n");
                LeftDrive.setMaxTorque(10,percent);
                RightDrive.setMaxTorque(10, percent);
                if(overwrite_countdown == 0)
                {
                    overwrite_countdown = 10;
                }
                else
                {
                    overwrite_countdown--;
                }
            }
            else
            {
                LeftDrive.setMaxTorque(100,percent);
                RightDrive.setMaxTorque(100,percent);
            }
        wait(15, msec);
    }
    return 0;
}
int dubugConsole()
{
    while(true)
    {
        printf("Imu Roll: %.2f\n", Imu.roll());
        printf("Imu Pitch: %.2f\n", Imu.pitch());
        wait(50,msec);
    }
}
int remote_controller_loop()
{
    while (RemoteControlCodeEnabled)
    {
      int lSpeed = Controller1.Axis3.position();
      int rSpeed = Controller1.Axis2.position();
      bool stop = abs(lSpeed) < deadZone && abs(rSpeed) < deadZone;
      if (stop)
      {
        if (DrivetrainLNeedsToBeStopped_Controller1)
        {
          LeftDrive.stop();
          if (facingBack) RightDrive.stop();
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
        if (DrivetrainRNeedsToBeStopped_Controller1)
        {
          RightDrive.stop();
          if (facingBack) LeftDrive.stop();
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      }
      else
      {
        DrivetrainLNeedsToBeStopped_Controller1 = true;
        DrivetrainRNeedsToBeStopped_Controller1 = true;
        int lSpeedAdj = facingBack ? -rSpeed : lSpeed;
        int rSpeedAdj = facingBack ? -lSpeed : rSpeed;
        if (DrivetrainLNeedsToBeStopped_Controller1)
        {
          LeftDrive.setVelocity(smoothIt(lSpeedAdj, LeftDrive.velocity(percent)), percent);
          LeftDrive.spin(forward);
        }
        if (DrivetrainRNeedsToBeStopped_Controller1)
        {
          RightDrive.setVelocity(smoothIt(rSpeedAdj, RightDrive.velocity(percent)), percent);
          RightDrive.spin(forward);
        }
      }
      wait(20, msec);
    }
  return 0;
}
void drive_assist_Init()
{
    driverControl = true;
    printf("drive_controller_Init\n");
    task remote_controller_task(remote_controller_loop);
    task tourqueControl_task(tourqueControlRaw);
    task triballDetectLoop_task(triballDetectLoop);
    // task debugConsole_task(dubugConsole);
}