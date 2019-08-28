#include "../include/standard_allocator.h"

#include <malloc.h>

urb::StandardAllocator *urb::StandardAllocator::s_global = nullptr;

urb::StandardAllocator *urb::StandardAllocator::Global() {
    if (s_global == nullptr) return s_global = new StandardAllocator;
    else return s_global;
}

urb::StandardAllocator::StandardAllocator() {
    m_allocationLedger = 0;

    m_maxUsage = 0;
    m_currentUsage = 0;
}

urb::StandardAllocator::~StandardAllocator() {
    assert(m_allocationLedger == 0);
    assert(m_currentUsage == 0);
}

void urb::StandardAllocator::initialize() {
    m_allocationLedger = 0;

    m_maxUsage = 0;
    m_currentUsage = 0;
}
