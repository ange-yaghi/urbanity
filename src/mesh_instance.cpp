#include "../include/mesh_instance.h"

urb::MeshInstance::MeshInstance() {
    m_mesh = nullptr;
}

urb::MeshInstance::~MeshInstance() {
    /* void */
}

urb::math::Vector urb::MeshInstance::getTransformedVertex(int index) {
    // TODO
    return m_mesh->getVertex(index);
}
