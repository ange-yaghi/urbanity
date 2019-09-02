#include "../include/fsm_state.h"

urb::FsmState::FsmState() {
    m_fsm = nullptr;
}

urb::FsmState::~FsmState() {
    /* void */
}

void urb::FsmState::onEnter() {
    /* void */
}

urb::StateId urb::FsmState::step(math::real timeStep) {
    return NoState;
}

void urb::FsmState::onExit() {
    /* void */
}
