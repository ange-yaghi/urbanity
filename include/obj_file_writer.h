#ifndef URBANITY_OBJ_FILE_WRITER_H
#define URBANITY_OBJ_FILE_WRITER_H

#include <string>

namespace urb {

    class Mesh;

    class ObjFileWriter {
    public:
        ObjFileWriter();
        ~ObjFileWriter();

        void writeMesh(const std::string &fname, Mesh *mesh);
    };

} /* namespace urb */

#endif /* URBANITY_OBJ_FILE_WRITER_H */
