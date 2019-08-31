#ifndef URBANITY_SCENE_H
#define URBANITY_SCENE_H

#include "mesh_instance.h"

namespace urb {

    class Scene {
    public:
        Scene();
        ~Scene();

        int getMeshInstanceCount() const;
        const MeshInstance *getMeshInstance(int index) const;
    };

} /* namespace urb */

#endif /* URBANITY_SCENE_H */
