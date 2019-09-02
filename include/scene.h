#ifndef URBANITY_SCENE_H
#define URBANITY_SCENE_H

#include "mesh_instance.h"

#include <vector>

namespace urb {

    class Scene {
    public:
        Scene();
        ~Scene();

        int getMeshInstanceCount() const;
        const MeshInstance *getMeshInstance(int index) const;
        void addMeshInstance(MeshInstance *mesh);

    protected:
        std::vector<MeshInstance *> m_meshes;
    };

} /* namespace urb */

#endif /* URBANITY_SCENE_H */
