#ifndef URBANITY_FSM_TEST_STATE_H
#define URBANITY_FSM_TEST_STATE_H

#include "../include/fsm_state.h"

namespace urb {

    template <int ID>
    class FsmTestState : public FsmState {
    public:
        FsmTestState() {
            /* void */
        }

        ~FsmTestState() {
            /* void */
        }
    };

} /* namespace urb */

#endif /* URBANITY_FSM_TEST_STATE_H */
