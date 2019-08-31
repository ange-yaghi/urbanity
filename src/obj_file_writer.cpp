#include "../include/obj_file_writer.h"

#include "../include/mesh.h"

urb::ObjFileWriter::ObjFileWriter() {
    // TODO
}

urb::ObjFileWriter::~ObjFileWriter() {
    // TODO
}

void urb::ObjFileWriter::writeScene(const std::string &fname, Scene *scene) {
    m_outputFile.open(fname, std::ios::out);
    if (!m_outputFile.is_open()) return;

    int nInstances = scene->getMeshInstanceCount();
    for (int i = 0; i < nInstances; i++) {
        const MeshInstance *meshInstance = scene->getMeshInstance(i);
        writeMeshInstance(meshInstance);
    }

    m_outputFile.close();
}

void urb::ObjFileWriter::writeHeader() {
    m_outputFile << "# Urbanity OBJ file\n";
    m_outputFile << "# https://github.com/ange-yaghi/urbanity\n";
}

void urb::ObjFileWriter::writeMeshInstance(const MeshInstance *mesh) {
    // TODO
}

void urb::ObjFileWriter::writeVertex(const math::Vector &v) {
    // TODO
}

void urb::ObjFileWriter::writeNormal(const math::Vector &n) {
    // TODO
}

void urb::ObjFileWriter::writeTexCoords(const math::Vector &t) {
    // TODO
}

void urb::ObjFileWriter::writeFace(const Mesh::Face &face) {
    // TODO
}
