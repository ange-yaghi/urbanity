#ifndef URBANITY_MESH_H
#define URBANITY_MESH_H

#include "math.h"

namespace urb {

    class Mesh {
    public:
        struct Face {
            int v1, v2, v3;
            int n1, n2, n3;
            int t1, t2, t3;
        };

    public:
        Mesh();
        ~Mesh();

        void initialize(int vertexCount, int normalCount, int texCoordCount, int faceCount);
        void destroy();

        math::Vector getVertex(int index) const { return m_vertices[index]; }
        void setVertex(int index, const math::Vector &v) { m_vertices[index] = v; }
        int getVertexCount() const { return m_vertexCount; }

        math::Vector getNormal(int index) const { return m_normals[index]; }
        void setNormal(int index, const math::Vector &n) { m_normals[index] = n; }
        int getNormalCount() const { return m_normalCount; }

        math::Vector getTexCoord(int index) const { return m_textureCoordinates[index]; }
        void setTexCoord(int index, const math::Vector &t) { m_textureCoordinates[index] = t; }
        int getTexCoordCount() const { return m_texCoordCount; }

        Face *getFace(int index) { return &m_faces[index]; }
        int getFaceCount() const { return m_faceCount; }

    protected:
        math::Vector *m_vertices;
        math::Vector *m_normals;
        math::Vector *m_textureCoordinates;
        Face *m_faces;

        int m_vertexCount;
        int m_normalCount;
        int m_texCoordCount;
        int m_faceCount;
    };

} /* namespace urb */

#endif /* URBANITY_MESH_H */
