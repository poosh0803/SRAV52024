#include "../include/vex.h"
#include "../include/robot-config.h"
#include "vex_global.h"
#include "vex_task.h"
#include "vex_units.h"
#include <cmath>
#include <vector>
#include "pid.h"

namespace Vision {

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
    vex::vision::object *mogoPort = leftMostObject(visionFilterHorizon(&mogoPortCam, 100));

    // If the mogo is not found, return 0 to maintain the current heading
    if (mogoStarboard == NULL || mogoPort == NULL) {
        printf("Mogo not found\n");
        return 0;
    }

    // Calculate the angle to turn
    // TODO: Tune the constant 15.0
    return (mogoStarboard->centerX + mogoPort->centerX - 310.0) / 15.0;
}

}; // namespace Vision