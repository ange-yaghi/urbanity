#ifndef URBANITY_DRONE_FSM_H
#define URBANITY_DRONE_FSM_H

#include "fsm.h"

namespace urb {

    class DroneFsm : public Fsm<DroneFsm> {
    public:
        DroneFsm();
        ~DroneFsm();

        FSM_STATES {
            /* empty */
        }
    };

} /* namespace urb */

#endif /* URBANITY_DRONE_FSM_H */
