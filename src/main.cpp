#include "../include/math.h"
#include "../include/simulator.h"
#include "../include/obj_file_writer.h"

#include <iostream>

int main() {
    urb::Scene scene;
    urb::Simulator simulator;

    simulator.setStartTime((urb::math::real)0.0);
    simulator.setEndTime((urb::math::real)1.0);
    simulator.setTimeStep((urb::math::real)0.1);

    simulator.run();
    simulator.generateGeometry(&scene);

    urb::ObjFileWriter objFileWriter;
    objFileWriter.writeScene("test.obj", &scene);

	return 0;
}
