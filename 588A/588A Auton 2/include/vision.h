#include <vector>
#include "vex.h"

namespace Vision {

std::vector <vex::vision::object *> visionFilterHorizon(vex::vision *visionSensor, uint16_t horizon);
vex::vision::object * rightMostObject(std::vector<vex::vision::object *> visionObjects);
vex::vision::object * leftMostObject(std::vector<vex::vision::object *> visionObjects);
double getMogoAngle();

}; // namespace Vision

