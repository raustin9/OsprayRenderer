#include <iostream>
#include "lib/renderer.h"

int main(int argc, const char** argv) {
	renderer::Renderer renderer = renderer::Renderer(1024, 768);

	renderer.initialize_ospray(&argc, argv);
	renderer.setup_device(renderer::DeviceKind::OSP_CPU);
	renderer.create_world();
	renderer.create_group();
	// renderer.setup_device(renderer::OSPDeviceType::OSP_GPU);
	renderer.shutdown();

    return EXIT_SUCCESS;
}
