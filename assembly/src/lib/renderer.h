#pragma once
#include <cstdio>
#include <memory>

#include "defines.h"
#include "osp.inl"
#include "device.h"

namespace renderer {

class Renderer {
public:
	Renderer(u32 width, u32 height)
	:   m_img_width(width),
	    m_img_height(height),
		m_is_initialized(false),
		m_device(nullptr)
	{}
	~Renderer() {
		if (m_is_initialized) {
			shutdown();
		}
	}
	
	bool initialize_ospray(i32 *argc, const char **argv);
	bool setup_device(DeviceKind device_type);
	bool create_world();
	bool create_group();
	bool finalize_group();
	bool shutdown();

	bool add_model();
	bool add_instance(OSPInstance instance);
private:
	u32 m_img_width, m_img_height; // the dimensions of the image to render
	bool m_is_initialized; // whether the renderer has been initialized yet
	std::unique_ptr<OspDevice> m_device;    // the device to run on. Either CPU or GPU. Released after being commited
	OSPWorld m_world;      // the world for the scene. Gets released at shutdown
	OSPGroup m_group;      // the group to hold all the models. Released at shutdown
};

}
