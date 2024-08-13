#include"../include/vex.h"
#include "../include/robot-config.h"
#include "../include/drive-controller.h"
#include "vex_brain.h"
#include <string>
double VERSION = 3.2;
int page = 1;
bool safeModeDis = true;
void lines()
{
    Brain.Screen.clearScreen();
    Brain.Screen.drawImageFromFile("capybara.png", 0, 0);
    Brain.Screen.setPenColor(vex::color::white);
    Brain.Screen.setPenWidth(2);
    Brain.Screen.drawLine(0, 136, 240, 136);
    Brain.Screen.drawLine(240, 0, 240, 272);
    // Brain.Screen.drawLine(0, 60, 240, 60);
    // Brain.Screen.drawLine(120, 0, 120, 120);
    Brain.Screen.drawLine(240, 200, 480, 200);
    Brain.Screen.drawLine(400, 200, 400, 272);
    Brain.Screen.setFont(vex::fontType::mono15);
    // Brain.Screen.printAt(5,10,"Current");
    // Brain.Screen.printAt(125,10,"Power");
    Brain.Screen.setFont(vex::fontType::cjk16);
    Brain.Screen.printAt(5,171,"Battery");
    // Brain.Screen.printAt(5,80,"D-Mode");
    // Brain.Screen.printAt(125,80,"LIM");
    Brain.Screen.setFont(vex::fontType::prop20);
    Brain.Screen.printAt(420,230,"v%.1f", (float)VERSION);
}
int batteryGraph()
{
    while(true)
    {
        Brain.Screen.setFont(vex::fontType::prop60);
        Brain.Screen.printAt(106, 200, "%.0f %c", (float)Brain.Battery.capacity(percent), '%');
        // Brain.Screen.setFont(vex::fontType::prop30);
        // Brain.Screen.printAt(10, 40, "%.2f", (float)Brain.Battery.current());
        // Brain.Screen.setFont(vex::fontType::cjk16);
        // Brain.Screen.printAt(70, 40, "Amps");
        // Brain.Screen.setFont(vex::fontType::prop30);
        // Brain.Screen.printAt(130, 40, "%.1f", (float)Brain.Battery.current()*Brain.Battery.voltage());
        // Brain.Screen.setFont(vex::fontType::cjk16);
        // Brain.Screen.printAt(190, 40, "Watts");
        wait(400, msec);
    }
    return 0;
}
void checkTemp(int index)
{
    switch (index)
    {
        case 1:
            if(L1.temperature(percent) >= 60)
            {
                Brain.Screen.setPenColor(vex::color::red);
            }
            else if (L1.temperature(percent) >= 40)
            {
                Brain.Screen.setPenColor(vex::color::yellow);
            }
            else
            {
                Brain.Screen.setPenColor(vex::color::green);
            }
            break;
        case 2:
            if(L2.temperature(percent) >= 60)
            {
                Brain.Screen.setPenColor(vex::color::red);
            }
            else if (L2.temperature(percent) >= 40)
            {
                Brain.Screen.setPenColor(vex::color::yellow);
            }
            else
            {
                Brain.Screen.setPenColor(vex::color::green);
            }
            break;
        case 3:
            if(L3.temperature(percent) >= 60)
            {
                Brain.Screen.setPenColor(vex::color::red);
            }
            else if (L3.temperature(percent) >= 40)
            {
                Brain.Screen.setPenColor(vex::color::yellow);
            }
            else
            {
                Brain.Screen.setPenColor(vex::color::green);
            }
            break;
        case 4:
            if(R1.temperature(percent) >= 60)
            {
                Brain.Screen.setPenColor(vex::color::red);
            }
            else if (R1.temperature(percent) >= 40)
            {
                Brain.Screen.setPenColor(vex::color::yellow);
            }
            else
            {
                Brain.Screen.setPenColor(vex::color::green);
            }
            break;
        case 5:
            if(R2.temperature(percent) >= 60)
            {
                Brain.Screen.setPenColor(vex::color::red);
            }
            else if (R2.temperature(percent) >= 40)
            {
                Brain.Screen.setPenColor(vex::color::yellow);
            }
            else
            {
                Brain.Screen.setPenColor(vex::color::green);
            }
            break;
        case 6:
            if(R3.temperature(percent) >= 60)
            {
                Brain.Screen.setPenColor(vex::color::red);
            }
            else if (R3.temperature(percent) >= 40)
            {
                Brain.Screen.setPenColor(vex::color::yellow);
            }
            else
            {
                Brain.Screen.setPenColor(vex::color::green);
            }
            break;
        case 7:
            if(ShooterArm.temperature(percent) >= 60)
            {
                Brain.Screen.setPenColor(vex::color::red);
            }
            else if (ShooterArm.temperature(percent) >= 40)
            {
                Brain.Screen.setPenColor(vex::color::yellow);
            }
            else
            {
                Brain.Screen.setPenColor(vex::color::green);
            }
            break;
        case 8:
            if(Intake.temperature(percent) >= 60)
            {
                Brain.Screen.setPenColor(vex::color::red);
            }
            else if (Intake.temperature(percent) >= 40)
            {
                Brain.Screen.setPenColor(vex::color::yellow);
            }
            else
            {
                Brain.Screen.setPenColor(vex::color::green);
            }
            break;
    }
}
void checkConnect(int index)
{
    if(index == 7)
    {
        if(!connection[index-1] || !connection[index])
        {
            Brain.Screen.setPenColor(vex::color::red);
        }
        else
        {
            Brain.Screen.setPenColor(vex::color::green);
            checkTemp(index);
        }
    }
    else if(!connection[index-1])
    {
        Brain.Screen.setPenColor(vex::color::red);
    }
    else
    {
        Brain.Screen.setPenColor(vex::color::green);
        checkTemp(index);
    }
}
void sensorCheck(int index)
{
    if(!sensors[index-1])
    {
        Brain.Screen.setPenColor(vex::color::red);
    }
    else
    {
        Brain.Screen.setPenColor(vex::color::green);
    }
}
void sensorsDisplay()
{
    selfCheck();
    Brain.Screen.setFont(vex::fontType::prop20);
    sensorCheck(1);
    Brain.Screen.printAt(413, 20, "Inertial");
    sensorCheck(2);
    Brain.Screen.printAt(405, 45, "BallDetecter");
    sensorCheck(3);
    Brain.Screen.printAt(390, 70, "Controller");
}
int tempGraph()
{
    while(true)
    {
        if(page == 1)
        {
            selfCheck();
            Brain.Screen.setFont(vex::fontType::prop20);
            checkConnect(1);
            Brain.Screen.printAt(245, 20, "Left1  : %d c", (int)L1.temperature(percent));
            checkConnect(2);
            Brain.Screen.printAt(245, 40, "Left2  : %d c", (int)L2.temperature(percent));
            checkConnect(3);
            Brain.Screen.printAt(245, 60, "Left3  : %d c", (int)L3.temperature(percent));
            checkConnect(4);
            Brain.Screen.printAt(245, 90, "Right1 : %d c", (int)R1.temperature(percent));
            checkConnect(5);
            Brain.Screen.printAt(245, 110, "Right2 : %d c", (int)R2.temperature(percent));
            checkConnect(6);
            Brain.Screen.printAt(245, 130, "Right3 : %d c", (int)R3.temperature(percent));
            checkConnect(7);
            Brain.Screen.printAt(245, 160, "BigArm: %d c", (int)ShooterArm.temperature(percent));
            checkConnect(8);
            Brain.Screen.printAt(245, 180, "Intake : %d c", (int)Intake.temperature(percent));
            wait(3000, msec);
        }
        else
        {
            wait(200, msec);
        }
    }
    return 0;
}
void controlMenu()
{
    Brain.Screen.setFont(vex::fontType::prop20);
    Brain.Screen.setPenColor(vex::color::white);
    Brain.Screen.printAt(245, 20, "Drive:   Tank Drive");
    if(safeModeDis) {Brain.Screen.printAt(245, 42, "X : Safe Mode");}
    else {Brain.Screen.printAt(245, 42, "X : MatchLoad");}
    Brain.Screen.printAt(245, 64, "Y : Side Wall");
    Brain.Screen.printAt(245, 86, "A : Adj-Shoot");
    Brain.Screen.printAt(245, 108, "B : ________");
    Brain.Screen.printAt(365, 42, "L1: Intake");
    Brain.Screen.printAt(365, 64, "L2: Outtake");
    Brain.Screen.printAt(365, 86, "R1: Shoot");
    Brain.Screen.printAt(365, 108, "R2: Brake");
}
void safeModeDisplay(bool safe)
{
    safeModeDis = safe;
    if(safe)
    {
        Brain.Screen.setPenColor(vex::color::green);
        Brain.Screen.setFont(vex::fontType::mono15);
        Brain.Screen.printAt(5, 240, "Safe Mode");
    }
    else
    {
        Brain.Screen.setPenColor(vex::color::black);
        Brain.Screen.setFillColor(vex::color::black);
        Brain.Screen.drawRectangle(5,230,80,20);
    }
}
void screenButtonCheck()
{
    //Temp Page Button
    if(Brain.Screen.xPosition() >= 240 && Brain.Screen.xPosition() <= 480 && Brain.Screen.yPosition() >= 0 && Brain.Screen.yPosition() <= 200)
    {
        if(page == 1)
        {
            page = 2;
            Brain.Screen.setPenColor(vex::color::black);
            Brain.Screen.setFillColor(vex::color::black);
            Brain.Screen.drawRectangle(241,0,238,199);
            controlMenu();
        }
        else
        {
            page = 1;
            Brain.Screen.setPenColor(vex::color::black);
            Brain.Screen.setFillColor(vex::color::black);
            Brain.Screen.drawRectangle(241,0,238,199);
            sensorsDisplay();
        }
    }
}
void display_init()
{
    lines();
    Brain.Screen.pressed(screenButtonCheck);
    vex::thread battery(batteryGraph);
    vex::thread temp(tempGraph);
    sensorsDisplay();
}
// void display()
// {
//     //Brain.Screen.drawCircle(240, 120, 100, vex::color::green);
//     //Brain.Screen.drawLine(int x1, int y1, int x2, int y2);
//     Brain.Screen.drawRectangle(0, 0, 480, 240, vex::color::green);
//     // Brain.Screen.drawCircle(100, 200, 100, color::white);
//     Brain.Screen.drawImageFromFile("peppapig.png", 0, 0);
// }
// void display_init()
// {
//     Brain.Screen.clearScreen();
//     Brain.Screen.setCursor(1, 1);
//     wait(100, msec);
//     display();
//     printf("display initialized\n");
// }