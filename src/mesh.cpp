#include "../include/mesh.h"

#include "../include/standard_allocator.h"

#include <assert.h>

urb::Mesh::Mesh() {
    m_vertexCount = 0;
    m_normalCount = 0;
    m_texCoordCount = 0;
    m_faceCount = 0;

    m_vertices = nullptr;
    m_normals = nullptr;
    m_textureCoordinates = nullptr;
    m_faces = nullptr;
}

urb::Mesh::~Mesh() {
    assert(m_vertices == nullptr);
    assert(m_normals == nullptr);
    assert(m_textureCoordinates == nullptr);
    assert(m_faces == nullptr);
}

void urb::Mesh::initialize(int vertexCount, int normalCount, int texCoordCount, int faceCount) {
    m_vertexCount = vertexCount;
    m_normalCount = normalCount;
    m_texCoordCount = texCoordCount;
    m_faceCount = faceCount;

    m_vertices = StandardAllocator::Global()->allocate<math::Vector>(m_vertexCount, 16);
    m_normals = StandardAllocator::Global()->allocate<math::Vector>(m_normalCount, 16);
    m_textureCoordinates = StandardAllocator::Global()->allocate<math::Vector>(m_texCoordCount, 16);
    m_faces = StandardAllocator::Global()->allocate<Face>(m_faceCount);
}

void urb::Mesh::destroy() {
    StandardAllocator::Global()->aligned_free(m_vertices, m_vertexCount);
    StandardAllocator::Global()->aligned_free(m_normals, m_normalCount);
    StandardAllocator::Global()->aligned_free(m_textureCoordinates, m_texCoordCount);
    StandardAllocator::Global()->free(m_faces, m_faceCount);

    m_vertexCount = 0;
    m_normalCount = 0;
    m_texCoordCount = 0;
    m_faceCount = 0;

    m_vertices = nullptr;
    m_normals = nullptr;
    m_textureCoordinates = nullptr;
    m_faces = nullptr;
}
