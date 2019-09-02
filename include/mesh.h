#ifndef URBANITY_MESH_H
#define URBANITY_MESH_H

#include "math.h"

namespace urb {

    class Mesh {
    public:
        struct Face {
            struct Vertex {
                int v, n, t;
            };

            union {
                struct {
                    int v1, n1, t1;
                    int v2, n2, t2;
                    int v3, n3, t3;
                };

                Vertex v[3];
            };
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

        Face *getFace(int index) const { return &m_faces[index]; }
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
