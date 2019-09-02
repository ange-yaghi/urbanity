#include "../include/mesh_instance.h"

urb::MeshInstance::MeshInstance() {
    m_mesh = nullptr;
}

urb::MeshInstance::~MeshInstance() {
    /* void */
}

urb::math::Vector urb::MeshInstance::getTransformedVertex(int index) const {
    // TODO
    return m_mesh->getVertex(index);
}

urb::math::Vector urb::MeshInstance::getTransformedNormal(int index) const {
    // TODO
    return m_mesh->getNormal(index);
}
