#include "../include/vex.h"
#include "../include/robot-config.h"
#include "../include/vision.h"
#include "../include/logger.h"
#include "../include/pid.h"
#include "vex_global.h"
#include "vex_task.h"
#include "vex_units.h"
#include <cmath>
#include <vector>

namespace Vision {

int mogoTrackStatus = LOST;
double lastMogoTime = 0;

vex::vision::object *prevMogoStarboard = NULL;
vex::vision::object *prevMogoPort = NULL;

std::vector<vex::vision::object *> visionFilterHorizon(vex::vision *visionSensor, uint16_t horizon) {
    std::vector<vex::vision::object *> visionObjects;

    for (int x = 0; x < visionSensor->objectCount; x++) {
        if (visionSensor->objects[x].centerY > horizon &&
            visionSensor->objects[x].width > 20)
        visionObjects.push_back(&visionSensor->objects[x]);
    }

    return visionObjects;
}

vex::vision::object * rightMostObject(std::vector<vex::vision::object *> visionObjects) {
    uint16_t centerX = 0;
    vex::vision::object *obj = NULL;

    for (int x = 0; x < visionObjects.size(); x++) {
        if (visionObjects[x]->centerX > centerX) {
            centerX = visionObjects[x]->centerX;
            obj = visionObjects[x];
        }
    }

    return obj;
}

vex::vision::object * leftMostObject(std::vector<vex::vision::object *> visionObjects) {
    uint16_t centerX = 9999;
    vex::vision::object *obj = NULL;

    for (int x = 0; x < visionObjects.size(); x++) {
        if (visionObjects[x]->centerX < centerX) {
            centerX = visionObjects[x]->centerX;
            obj = visionObjects[x];
        }
    }

    return obj;
}

double getMogoAngle() {
    mogoStarboardCam.takeSnapshot(mogoStarboardCam__MOGO);
    mogoPortCam.takeSnapshot(mogoPortCam__MOGO);

    // Get the vision sensor object
    vex::vision::object *mogoStarboard = rightMostObject(visionFilterHorizon(&mogoStarboardCam, 100));
    vex::vision::object *mogoPort = rightMostObject(visionFilterHorizon(&mogoPortCam, 100));

    // If the mogo detection stale, continue to use the previous data until it is >0.5s old
    if (mogoStarboard == NULL || mogoPort == NULL) {
        if (Brain.Timer.value() - lastMogoTime > staleTime) {
            mogoTrackStatus = LOST;
            return 0;
        } else {
            mogoTrackStatus = STALE;
            mogoStarboard == NULL ? mogoStarboard = prevMogoStarboard : mogoStarboard;
            mogoPort == NULL ? mogoPort = prevMogoPort : mogoPort;
        }
    } else {
        mogoTrackStatus = TRACKING;
        lastMogoTime = Brain.Timer.value();
    }


    // Calculate the angle to turn
    // TODO: Tune the constant 15.0
    if (mogoStarboard != NULL && mogoPort != NULL) {
        return (mogoStarboard->centerX + mogoPort->centerX - center) * visionKP;
    }
    
    return 0;
}

void testVision() {
    Imu.setHeading(0, degrees);
    pid_Init();
    mogoGOUP();

    drive_w_PID(reverse, 100, inches, 80, true);
    mogoGODOWN();
}

}; // namespace Vision