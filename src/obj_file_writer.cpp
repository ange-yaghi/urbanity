#include "../include/obj_file_writer.h"

#include "../include/mesh.h"

#include <fstream>

urb::ObjFileWriter::ObjFileWriter() {
    m_currentVertex = 0;
    m_currentTexCoord = 0;
    m_currentNormal = 0;

    m_outputStream = nullptr;
}

urb::ObjFileWriter::~ObjFileWriter() {
    // TODO
}

void urb::ObjFileWriter::writeScene(std::ostream *stream, Scene *scene) {
    m_outputStream = stream;

    writeHeader();

    int nInstances = scene->getMeshInstanceCount();
    for (int i = 0; i < nInstances; i++) {
        const MeshInstance *meshInstance = scene->getMeshInstance(i);
        writeMeshInstance(meshInstance);
    }

    m_outputStream = nullptr;
}

void urb::ObjFileWriter::writeScene(const std::string &fname, Scene *scene) {
    std::fstream outputFile(fname, std::ios::out);
    if (!outputFile.is_open()) return;

    writeScene(&outputFile, scene);

    outputFile.close();
}

void urb::ObjFileWriter::writeHeader() {
    writeComment("Urbanity OBJ file");
    writeComment("https://github.com/ange-yaghi/urbanity");
}

void urb::ObjFileWriter::writeMeshInstance(const MeshInstance *mesh) {
    int vertexCount = mesh->getVertexCount();
    for (int i = 0; i < vertexCount; i++) {
        writeVertex(mesh->getTransformedVertex(i));
    }

    int normalCount = mesh->getNormalCount();
    for (int i = 0; i < normalCount; i++) {
        writeNormal(mesh->getTransformedNormal(i));
    }

    int texCoordCount = mesh->getMesh()->getTexCoordCount();
    for (int i = 0; i < texCoordCount; i++) {
        writeTexCoords(mesh->getMesh()->getTexCoord(i));
    }

    int faceCount = mesh->getMesh()->getFaceCount();
    for (int i = 0; i < faceCount; i++) {
        writeFace(*mesh->getMesh()->getFace(i));
    }

    m_currentVertex += vertexCount;
    m_currentNormal += normalCount;
    m_currentTexCoord += texCoordCount;
}

void urb::ObjFileWriter::writeVertex(const math::Vector &v) {
    *m_outputStream
        << "v "
        << math::getX(v) << " "
        << math::getY(v) << " "
        << math::getZ(v)
        << std::endl;
}

void urb::ObjFileWriter::writeNormal(const math::Vector &n) {
    *m_outputStream
        << "vn "
        << math::getX(n) << " "
        << math::getY(n) << " "
        << math::getZ(n)
        << std::endl;
}

void urb::ObjFileWriter::writeTexCoords(const math::Vector &t) {
    *m_outputStream
        << "vt "
        << math::getX(t) << " "
        << math::getY(t)
        << std::endl;
}

void urb::ObjFileWriter::writeFace(const Mesh::Face &face) {
    *m_outputStream << "f ";

    constexpr int VERTEX_COUNT = 3;
    for (int i = 0; i < VERTEX_COUNT; i++) {
        writeIndex(face.v[i].v, m_currentVertex); *m_outputStream << "/";
        writeIndex(face.v[i].n, m_currentNormal); *m_outputStream << "/";
        writeIndex(face.v[i].t, m_currentTexCoord);

        if (i != VERTEX_COUNT - 1) {
            *m_outputStream << " ";
        }
    }

    *m_outputStream << std::endl;
}

void urb::ObjFileWriter::writeComment(const std::string &comment) {
    *m_outputStream << "# " << comment << "\n";
}

void urb::ObjFileWriter::writeIndex(int index, int offset) {
    if (index != -1) {
        *m_outputStream << (index + 1 + offset);
    }
}
