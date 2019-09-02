#ifndef URBANITY_OBJ_FILE_WRITER_H
#define URBANITY_OBJ_FILE_WRITER_H

#include "mesh_instance.h"
#include "scene.h"

#include <string>
#include <ostream>

namespace urb {

    class ObjFileWriter {
    public:
        ObjFileWriter();
        ~ObjFileWriter();

        void writeScene(std::ostream *stream, Scene *scene);
        void writeScene(const std::string &fname, Scene *scene);

    protected:
        void writeHeader();
        void writeMeshInstance(const MeshInstance *mesh);

    protected:
        void writeVertex(const math::Vector &v);
        void writeNormal(const math::Vector &n);
        void writeTexCoords(const math::Vector &t);
        void writeFace(const Mesh::Face &face);
        void writeComment(const std::string &comment);

        void writeIndex(int index, int offset);

    protected:
        std::ostream *m_outputStream;

        int m_currentVertex;
        int m_currentNormal;
        int m_currentTexCoord;
    };

} /* namespace urb */

#endif /* URBANITY_OBJ_FILE_WRITER_H */
