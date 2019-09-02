#ifndef URBANITY_SIMULATOR_H
#define URBANITY_SIMULATOR_H

#include "math.h"
#include "simulation_object.h"
#include "standard_allocator.h"
#include "scene.h"

#include <vector>

namespace urb {

    class Simulator {
    public:
        class SimulationFrame {
        public:
            SimulationObject *getAddedObject(int index) { return m_addedObjects[index]; }
            void addObject(SimulationObject *object) { m_addedObjects.push_back(object); }
            int getAddedObjectCount() const { return (int)m_addedObjects.size(); }

            SimulationObject *getDeletedObject(int index) { return m_deletedObjects[index]; }
            void deleteObject(SimulationObject *object) { m_deletedObjects.push_back(object); }
            int getDeletedObjectCount() const { return (int)m_deletedObjects.size(); }

        protected:
            std::vector<SimulationObject *> m_addedObjects;
            std::vector<SimulationObject *> m_deletedObjects;
        };

    public:
        Simulator();
        ~Simulator();

        void setTimeStep(math::real timeStep) { m_timeStep = timeStep; }
        math::real getTimeStep() const { return m_timeStep; }

        void setStartTime(math::real startTime) { m_startTime = startTime; }
        math::real getStartTime() const { return m_startTime; }

        void setEndTime(math::real endTime) { m_endTime = endTime; }
        math::real getEndTime() const { return m_endTime; }

        int getObjectCount() const { return (int)m_objects.size(); }

        template <typename SimulationObjectType>
        SimulationObjectType *createObject() {
            SimulationObjectType *newObject =
                StandardAllocator::Global()->allocate<SimulationObjectType>(1, 16);
            newObject->setSimulator(this);

            // Add the object to the object list (or frame buffer)
            if (m_currentFrame == nullptr) {
                m_objects.push_back(newObject);
                newObject->setIndex(getObjectCount() - 1);
            }
            else {
                m_currentFrame->addObject(newObject);
            }
        }

        void deleteObject(SimulationObject *object);

        void run();
        void generateGeometry(Scene *scene);

    protected:
        void step(math::real timeStep);

    protected:
        math::real m_timeStep;
        math::real m_startTime;
        math::real m_endTime;

    protected:
        SimulationFrame *m_currentFrame;

        void updateObjectList(SimulationFrame *frame);
        void destroyObject(SimulationObject *object);
        void pruneObjectList();
        std::vector<SimulationObject *> m_objects;
    };

} /* namespace urb */

#endif /* URBANITY_SIMULATOR_H */
