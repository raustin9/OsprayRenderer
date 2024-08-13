#include "renderer.h"
#include "ospray/ospray.h"

namespace renderer {

// Initialize ospray for rendering
bool Renderer::initialize_ospray(i32 *argc, const char **argv) {
	std::printf("Renderer: Initializing OSPRay... ");
	OSPError err = ospInit(argc, argv);
	if (err != OSP_NO_ERROR) {
		std::printf("error initializing OSPRay.\n");
		return false;
	}

	m_is_initialized = true;
	std::printf("done.\n");
	return true;
}

// Setup behavior for the ospray device
bool Renderer::setup_device(DeviceKind device_kind) {
	if (!m_device) {
		m_device = std::make_unique<OspDevice>(OspDevice(device_kind));
		return true;
	} else {
		std::printf("ERROR: Cannot create device that is already created!\n");
		return false;
	}
}

// Shutdown behavior for the renderer
bool Renderer::shutdown() {
	if (!m_is_initialized) {
		std::printf("ERROR: Renderer: shutdown: Cannot shutdown uninitialized renderer.\n");
		return false;
	}
	std::printf("Renderer: Shutting down OSPRay... ");

	ospRelease(m_group);
	ospRelease(m_world);

	ospShutdown();
	m_is_initialized = false;

	std::printf("done.\n");
	return true;
}

// Create the OSPRay world for the scene
bool Renderer::create_world() {
	std::printf("Renderer: Creating world... ");
	if (!m_is_initialized) {
		std::printf("    ERROR: Renderer: create_world: cannot perform actions on uninitialized renderer..\n");
		return false;
	}
	m_world = ospNewWorld();
	std::printf("done.\n");
	
	return true;
}

// Create the group for the models
bool Renderer::create_group() {
	std::printf("Renderer: Creating group... ");
	if (!m_is_initialized) {
		std::printf("    ERROR: Renderer: create_group: cannot perform actions on uninitialized renderer..\n");
		return false;
	}

	m_group = ospNewGroup();

	std::printf("done.\n");
	
	return true;
}

// Finalize the group
bool Renderer::finalize_group() {
	std::printf("Renderer: Finalizing group: ");

	std::printf("    Creating instance from group.\n");
	OSPInstance instance = ospNewInstance(m_group);
	
	std::printf("    Committing instance.\n");
	ospCommit(instance);

	std::printf("    Adding instance to the world");
	ospSetObjectAsData(m_world, "instance", OSP_INSTANCE, instance);
	
	std::printf("    Releasing instance.");
	ospRelease(instance);
	// ospRelease(m_group);
	std::printf("    Done.");

	return true;
}

// Add an instance to the world
bool Renderer::add_instance(OSPInstance instance) {
	return true;
}

// TODO:
// add a new model. This requires having geometric models
// and addign them to the groups
bool Renderer::add_model() {
	return true;
}

} // renderer namespace
