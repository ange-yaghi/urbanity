#include "../include/fsm.h"

urb::FsmInterface::FsmInterface() {
    /* void */
}

urb::FsmInterface::~FsmInterface() {
    int stateCount = getStateCount();
    for (int i = 0; i < stateCount; i++) {
        StandardAllocator::Global()->aligned_free(m_states[i]);
    }
}

void urb::FsmInterface::initialize() {
    registerStates();
}

void urb::FsmInterface::step(math::real timeStep) {
    if (m_currentState == FsmState::NoState) {
        if (getStateCount() == 0) return;
        else changeState(DEFAULT_STATE);
    }

    StateId newState = m_states[m_currentState]->step(timeStep);
    if (newState != m_currentState) {
        changeState(newState);
    }
}

void urb::FsmInterface::changeState(StateId newState) {
    if (m_currentState != FsmState::NoState) {
        m_states[m_currentState]->onExit();
    }

    if (newState == FsmState::NoState) return;

    m_currentState = newState;
    m_states[m_currentState]->onEnter();
}
