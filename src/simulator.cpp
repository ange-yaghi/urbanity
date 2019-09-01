#include "../include/simulator.h"

urb::Simulator::Simulator() {
    m_timeStep = (math::real)0.0;
    m_startTime = (math::real)0.0;
    m_endTime = (math::real)0.0;

    m_currentFrame = nullptr;
}

urb::Simulator::~Simulator() {
    m_currentFrame = nullptr;

    int objectCount = getObjectCount();
    for (int i = 0; i < objectCount; i++) {
        destroyObject(m_objects[i]);
        m_objects[i] = nullptr;
    }

    pruneObjectList();
}

void urb::Simulator::deleteObject(SimulationObject *object) {
    if (m_currentFrame == nullptr) {
        m_objects[object->getIndex()] = nullptr;
        pruneObjectList();
        destroyObject(object);
    }
    else {
        m_currentFrame->deleteObject(object);
        object->setDeleted(true);
    }
}

void urb::Simulator::run() {
    math::real currentTime = m_startTime;
    unsigned __int64 currentIndex = 0;
    while (currentTime <= m_endTime) {
        SimulationFrame frame;
        m_currentFrame = &frame;
        step(m_timeStep);

        updateObjectList(&frame);

        currentIndex++;
        currentTime = currentIndex * m_timeStep + m_startTime;
    }
}

void urb::Simulator::generateGeometry(Scene *scene) {
    /* void */
}

void urb::Simulator::step(math::real timeStep) {
    int objectCount = getObjectCount();
    for (int i = 0; i < objectCount; i++) {
        SimulationObject *object = m_objects[i];

        if (!object->isDeleted()) {
            m_objects[i]->step(timeStep);
        }
    }
}

void urb::Simulator::updateObjectList(SimulationFrame *frame) {
    int deletedObjects = frame->getDeletedObjectCount();
    for (int i = 0; i < deletedObjects; i++) {
        SimulationObject *deletedObject = frame->getDeletedObject(i);
        m_objects[i] = nullptr;
        destroyObject(deletedObject);
    }

    pruneObjectList();

    int addedObjects = frame->getAddedObjectCount();
    for (int i = 0; i < addedObjects; i++) {
        SimulationObject *addedObject = frame->getAddedObject(i);
        m_objects.push_back(addedObject);
        addedObject->setIndex(getObjectCount() - 1);
    }
}

void urb::Simulator::destroyObject(SimulationObject *object) {
    StandardAllocator::Global()->aligned_free(object);
}

void urb::Simulator::pruneObjectList() {
    int objectCount = getObjectCount();
    int newSize = 0;
    for (int i = 0; i < objectCount; i++) {
        if (m_objects[i] != nullptr) {
            SimulationObject *object = m_objects[i];
            object->setIndex(newSize);
            m_objects[newSize++] = object;
        }
    }

    m_objects.resize(newSize);
}
