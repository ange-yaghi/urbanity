#include "../include/obj_file_loader.h"

#include "../include/standard_allocator.h"
#include "../include/mesh.h"

#include <fstream>
#include <sstream>
#include <cctype>
#include <functional>
#include <string>

// Taken from https://www.oreilly.com/library/view/c-cookbook/0596007612/ch04s07.html
template<typename T>
void split(const std::basic_string<T>& s, T c, std::vector<std::basic_string<T> >& v) {
    typename std::basic_string<T>::size_type i = 0;
    typename std::basic_string<T>::size_type j = s.find(c);

    if (j == std::basic_string<T>::npos) {
        v.push_back(std::string(s));
        return;
    }

    while (j != std::basic_string<T>::npos) {
        v.push_back(s.substr(i, j - i));
        i = ++j;
        j = s.find(c, j);

        if (j == std::basic_string<T>::npos)
            v.push_back(s.substr(i, s.length()));
    }
}

bool isWhitespace(const std::string &s) {
    for (int i = 0; i < s.length(); i++) {
        if (!std::isspace(s[i])) {
            return false;
        }
    }
    return true;
}

urb::ObjFileLoader::ObjFileLoader() {
    m_currentLine = 0;
    m_currentMaterial = nullptr;
}

urb::ObjFileLoader::~ObjFileLoader() {
    // TODO: check that object is actually destroyed
}

bool urb::ObjFileLoader::loadObjFile(const std::string &fname) {
    std::ifstream inputFile(fname, std::ios::in);

    if (!inputFile.is_open()) return false;
    
    bool result = loadObjFile(inputFile);
    inputFile.close();

    return result;
}

void urb::ObjFileLoader::populateMesh(Mesh *mesh) const {
    int vertexCount = getVertexCount();
    int normalCount = getNormalCount();
    int texCoordCount = getTexCoordCount();
    int faceCount = getFaceCount();

    mesh->initialize(
        vertexCount,
        normalCount,
        texCoordCount,
        faceCount
    );

    for (int i = 0; i < vertexCount; i++) {
        const math::Vector3 &ref = *m_vertices[i];
        math::Vector v =
            math::loadVector(ref.x, ref.y, ref.z);

        mesh->setVertex(i, v);
    }

    for (int i = 0; i < normalCount; i++) {
        const math::Vector3 &ref = *m_normals[i];
        math::Vector n =
            math::loadVector(ref.x, ref.y, ref.z);

        mesh->setNormal(i, n);
    }

    for (int i = 0; i < texCoordCount; i++) {
        const math::Vector2 &ref = *m_texCoords[i];
        math::Vector v =
            math::loadVector(ref.x, ref.y);

        mesh->setTexCoord(i, v);
    }

    for (int i = 0; i < faceCount; i++) {
        const ObjFace &ref = *m_faces[i];
        Mesh::Face *face = mesh->getFace(i);

        for (int vi = 0; vi < 3; vi++) {
            face->v[vi].v = ref.v[vi] - 1;
            face->v[vi].n = ref.vn[vi] - 1;
            face->v[vi].t = ref.vt[vi] - 1;
        }
    }
}

bool urb::ObjFileLoader::loadObjFile(std::istream &stream) {
    m_currentLine = 0;
    m_currentMaterial = nullptr;

    for (std::string line; std::getline(stream, line); ) {
        m_currentLine++;
        std::stringstream ss(line);

        std::string firstWord;
        ss >> firstWord;

        // Skip this line if it's a comment
        if (firstWord[0] == '#') continue;
        else if (firstWord.compare("v") == 0) {
            // Create a new vertex
            math::Vector3 *newVertex = StandardAllocator::Global()->allocate<math::Vector3>();
            m_vertices.push_back(newVertex);
            bool result = readVertexPosition(ss, newVertex);
            if (!result) {
                return false;
            }
        }
        else if (firstWord.compare("vt") == 0) {
            // Read a texture coordinate
            math::Vector2 *texCoords = StandardAllocator::Global()->allocate<math::Vector2>();
            m_texCoords.push_back(texCoords);
            bool result = readVertexTextureCoords(ss, texCoords);
            if (!result) {
                return false;
            }
        }
        else if (firstWord.compare("vn") == 0) {
            // Read a normal value
            math::Vector3 *normal = StandardAllocator::Global()->allocate<math::Vector3>();
            m_normals.push_back(normal);
            bool result = readVertexNormal(ss, normal);
            if (!result) {
                return false;
            }
        }
        else if (firstWord.compare("f") == 0) {
            // Read a face
            ObjFace *newFace = StandardAllocator::Global()->allocate<ObjFace>();
            newFace->material = m_currentMaterial;
            m_faces.push_back(newFace);
            bool result = readFace(ss, newFace);
            if (!result) {
                return false;
            }
        }
        else if (firstWord.compare("usemtl") == 0) {
            // Use a new material
            bool result = readMaterial(ss);
            if (!result) {
                return false;
            }
        }
    }

    return true;
}

bool urb::ObjFileLoader::readVertexPosition(std::stringstream &s, math::Vector3 *vertex) const {
    s >> vertex->x;
    if (s.fail()) {
        return false;
    }

    s >> vertex->y;
    if (s.fail()) {
        return false;
    }

    s >> vertex->z;
    if (s.fail()) {
        return false;
    }

    if (!s.eof()) {
        return false;
    }
    else {
        return true;
    }
}

bool urb::ObjFileLoader::readVertexNormal(std::stringstream &s, math::Vector3 *vertex) const {
    s >> vertex->x;
    if (s.fail()) {
        return false;
    }

    s >> vertex->y;
    if (s.fail()) {
        return false;
    }

    s >> vertex->z;
    if (s.fail()) {
        return false;
    }

    if (!s.eof()) {
        return false;
    }
    else {
        return true;
    }
}

bool urb::ObjFileLoader::readVertexTextureCoords(std::stringstream &s, math::Vector2 *texCoords) const {
    s >> texCoords->x;
    if (s.fail()) {
        return false;
    }

    s >> texCoords->y;
    if (s.fail()) {
        return false;
    }

    if (!s.eof()) {
        return false;
    }
    else {
        return true;
    }
}

bool urb::ObjFileLoader::readFace(std::stringstream &s, ObjFace *face) {
    size_t nParameters = 0;
    int vertexIndex = 0;

    // Initialize all indices
    // NOTE: 0 corresponds to -1 since the indices will be transformed later
    for (int i = 0; i < 3; i++) {
        face->vt[i] = 0;
        face->vn[i] = 0;
        face->v[i] = 0;
    }

    while (!s.eof()) {
        std::string group;
        s >> group;

        std::vector<std::string> elements;
        split(group, '/', elements);

        if (nParameters == 0) nParameters = elements.size();
        else {
            if (nParameters != elements.size()) {
                return false;
            }
        }

        if (nParameters >= 1) {
            std::stringstream ss = std::stringstream(elements[0]);
            ss >> face->v[vertexIndex];
            if (ss.fail()) {
                return false;
            }
        }
        if (nParameters >= 2) {
            if (!isWhitespace(elements[1])) {
                std::stringstream ss = std::stringstream(elements[1]);
                ss >> face->vt[vertexIndex];
                if (ss.fail()) {
                    return false;
                }
            }
        }
        if (nParameters == 3) {
            if (!isWhitespace(elements[2])) {
                std::stringstream ss = std::stringstream(elements[2]);
                ss >> face->vn[vertexIndex];
                if (ss.fail()) {
                    return false;
                }
            }
        }
        if (nParameters > 3) { return false; }

        vertexIndex++;
    }

    return true;
}

bool urb::ObjFileLoader::readMaterial(std::stringstream &s) {
    std::string materialName;
    s >> materialName;

    if (s.fail()) {
        return false;
    }

    if (materialName == "None") {
        m_currentMaterial = nullptr;
    }
    else {
        ObjMaterial *newMaterial = StandardAllocator::Global()->allocate<ObjMaterial>();
        m_materials.push_back(newMaterial);
        newMaterial->name = materialName;
        m_currentMaterial = newMaterial;
    }

    return true;
}

void urb::ObjFileLoader::destroy() {
    for (std::vector<math::Vector3 *>::iterator it = m_vertices.begin(); it != m_vertices.end(); ++it) {
        StandardAllocator::Global()->free(*it);
    }

    for (std::vector<math::Vector3 *>::iterator it = m_normals.begin(); it != m_normals.end(); ++it) {
        StandardAllocator::Global()->free(*it);
    }

    for (std::vector<math::Vector2 *>::iterator it = m_texCoords.begin(); it != m_texCoords.end(); ++it) {
        StandardAllocator::Global()->free(*it);
    }

    for (std::vector<ObjFace *>::iterator it = m_faces.begin(); it != m_faces.end(); ++it) {
        StandardAllocator::Global()->free(*it);
    }

    for (std::vector<ObjMaterial *>::iterator it = m_materials.begin(); it != m_materials.end(); ++it) {
        StandardAllocator::Global()->free(*it);
    }
}
