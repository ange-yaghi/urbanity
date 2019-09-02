#ifndef URBANITY_FSM_STATE_H
#define URBANITY_FSM_STATE_H

#include "math.h"

namespace urb {

    typedef int StateId;

#define STATE(StateType) m_fsm->id<StateType>()

    class FsmState {
    public:
        static constexpr StateId NoState = -1;

    public:
        FsmState();
        ~FsmState();

        virtual void onEnter();
        virtual StateId step(math::real timeStep);
        virtual void onExit();

    protected:
        template <typename T_FsmState>
        StateId id();

        class FsmInterface *m_fsm;
    };

    class FsmStateWrapperInterface {
    public:
        FsmStateWrapperInterface(FsmState *state) {
            m_state = state;
        }

        ~FsmStateWrapperInterface() {
            /* void */
        }

        FsmState *getState() const { return m_state; }

    protected:
        FsmState *m_state;
    };

    template <typename T_FsmState, typename T_Fsm>
    class FsmStateWrapper : public FsmStateWrapperInterface {
    public:
        FsmStateWrapper(FsmState *state) : FsmStateWrapperInterface(state) {
            /* void */
        }

        ~FsmStateWrapper() {
            /* void */
        }

        static StateId getId() { return s_id; }
        static void setId(StateId id) { s_id = id; }

    protected:
        static StateId s_id;
    };

    template <typename T_FsmState, typename T_Fsm>
    StateId FsmStateWrapper<T_FsmState, T_Fsm>::s_id = FsmState::NoState;

} /* namespace urb */

#endif /* URBANITY_FSM_STATE_H */
