#ifndef URBANITY_SIMULATION_OBJECT_H
#define URBANITY_SIMULATION_OBJECT_H

#include "math.h"

namespace urb {

    class SimulationObject {
    public:
        SimulationObject();
        ~SimulationObject();

        virtual void step(math::real timeStep);

        int getIndex() const { return m_index; }
        void setIndex(int index) { m_index = index; }

        void setDeleted(bool deleted) { m_deleted = deleted; }
        bool isDeleted() const { return m_deleted; }

    private:
        int m_index;
        bool m_deleted;
    };

} /* namespace urb */

#endif /* URBANITY_SIMULATION_OBJECT_H */
