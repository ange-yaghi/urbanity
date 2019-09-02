#include "pch.h"

#include "../include/mesh.h"
#include "../include/obj_file_loader.h"
#include "../include/obj_file_writer.h"
#include "../include/scene.h"

#include <sstream>

TEST(ObjFileTests, ObjFileSanityCheck) {
    bool result;

    urb::ObjFileLoader objFileLoader;
    result = objFileLoader.loadObjFile("../../../test/assets/geometry/blocks.obj");

    EXPECT_TRUE(result);

    urb::Mesh mesh;
    objFileLoader.populateMesh(&mesh);

    urb::MeshInstance instance;
    instance.setMesh(&mesh);

    urb::Scene scene;
    scene.addMeshInstance(&instance);

    std::stringstream ss;
    urb::ObjFileWriter objFileWriter;

    objFileWriter.writeScene(&ss, &scene);
    std::string str = ss.str();
    std::istringstream i_ss(str);

    urb::ObjFileLoader testLoader;
    result = testLoader.loadObjFile(i_ss);

    EXPECT_TRUE(result);

    EXPECT_EQ(testLoader.getFaceCount(), objFileLoader.getFaceCount());
    EXPECT_EQ(testLoader.getVertexCount(), objFileLoader.getVertexCount());
    EXPECT_EQ(testLoader.getNormalCount(), objFileLoader.getNormalCount());
    EXPECT_EQ(testLoader.getTexCoordCount(), objFileLoader.getTexCoordCount());

    objFileLoader.destroy();
    mesh.destroy();
    testLoader.destroy();
}
