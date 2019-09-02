#ifndef URBANITY_DRONE_H
#define URBANITY_DRONE_H

#include "simulation_object.h"

#include "drone_fsm.h"

namespace urb {

    class Drone : public SimulationObject {
    public:
        Drone();
        ~Drone();

        void step(math::real timeStep);

    protected:
        DroneFsm m_fsm;
    };

} /* namespace urb */

#endif /* URBANITY_DRONE_H */
