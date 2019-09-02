#ifndef URBANITY_MESH_INSTANCE_H
#define URBANITY_MESH_INSTANCE_H

#include "mesh.h"

namespace urb {

    class MeshInstance {
    public:
        MeshInstance();
        ~MeshInstance();

        const Mesh *getMesh() const { return m_mesh; }
        void setMesh(const Mesh *mesh) { m_mesh = mesh; }

        math::Vector getTransformedVertex(int index) const;
        int getVertexCount() const { return m_mesh->getVertexCount(); }

        math::Vector getTransformedNormal(int index) const;
        int getNormalCount() const { return m_mesh->getNormalCount(); }

    protected:
        const Mesh *m_mesh;
    };

} /* namespace urb */

#endif /* URBANITY_MESH_INSTANCE */
