#ifndef URBANITY_FSM_H
#define URBANITY_FSM_H

#include "fsm_state.h"
#include "standard_allocator.h"

#include <vector>

namespace urb {

    class FsmInterface {
    public:
        static constexpr StateId DEFAULT_STATE = 0;

    public:
        FsmInterface();
        ~FsmInterface();

        int getStateCount() const { return (int)m_states.size(); }
        StateId getCurrentId() const { return getStateCount(); }

        void initialize();

        void step(math::real timeStep);

    protected:
        virtual void registerStates() = 0;

        void changeState(StateId newState);

    protected:
        StateId m_currentState;
        std::vector<FsmState *> m_states;
    };

#define FSM_STATES virtual void registerStates()
#define FSM_PARENT_STATES(parent) parent::registerStates();
#define FSM_STATE(state) registerState<state>();

    template <typename T_Fsm>
    class Fsm : public FsmInterface {
    public:
        Fsm() {
            /* void */
        }

        ~Fsm() {
            /* void */
        }

        template <typename T_FsmState>
        void registerState() {
            T_FsmState *newState =
                StandardAllocator::Global()->allocate<T_FsmState>(1, 16);
            
            FsmStateWrapper<T_FsmState, T_Fsm> wrapper(newState);
            FsmStateWrapper<T_FsmState, T_Fsm>::setId(getCurrentId());            

            m_states.push_back(newState);
        }

        template <typename T_FsmState>
        StateId id() {
            return FsmStateWrapper<T_FsmState, T_Fsm>::getId();
        }

    protected:
        virtual void registerStates() = 0;
    };

} /* namespace urb */

#endif /* URBANITY_FSM_H */
