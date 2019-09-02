#include "../include/scene.h"

urb::Scene::Scene() {
    /* void */
}

urb::Scene::~Scene() {
    /* void */
}

int urb::Scene::getMeshInstanceCount() const {
    return (int)m_meshes.size();
}

const urb::MeshInstance *urb::Scene::getMeshInstance(int index) const {
    return m_meshes[index];
}

void urb::Scene::addMeshInstance(MeshInstance *mesh) {
    m_meshes.push_back(mesh);
}
