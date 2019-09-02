#ifndef URBANITY_FSM_TEST_H
#define URBANITY_FSM_TEST_H

#include "../include/fsm.h"

#include "fsm_test_state.h"

namespace urb {

    class FsmTest : public Fsm<FsmTest> {
    public:
        FsmTest();
        ~FsmTest();

        FSM_STATES {
            FSM_STATE(FsmTestState<0>)
            FSM_STATE(FsmTestState<1>)
            FSM_STATE(FsmTestState<2>)
        }
    };

} /* namespace urb */

#endif /* URBANITY_FSM_TEST_H */
