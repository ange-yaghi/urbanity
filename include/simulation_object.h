#ifndef URBANITY_SIMULATION_OBJECT_H
#define URBANITY_SIMULATION_OBJECT_H

#include "math.h"

namespace urb {

    class Simulator;

    class SimulationObject {
    public:
        SimulationObject();
        ~SimulationObject();

        virtual void step(math::real timeStep);

        int getIndex() const { return m_index; }
        void setIndex(int index) { m_index = index; }

        void setDeleted(bool deleted) { m_deleted = deleted; }
        bool isDeleted() const { return m_deleted; }

        void setSimulator(Simulator *simulator) { m_simulator = simulator; }
        Simulator *getSimulator() const { return m_simulator; }

    private:
        int m_index;
        bool m_deleted;

        Simulator *m_simulator;
    };

} /* namespace urb */

#endif /* URBANITY_SIMULATION_OBJECT_H */
