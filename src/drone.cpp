#include "../include/drone.h"

urb::Drone::Drone() {
    /* void */
}

urb::Drone::~Drone() {
    /* void */
}

void urb::Drone::step(math::real timeStep) {
    m_fsm.step(timeStep);
}
