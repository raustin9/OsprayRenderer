#include "device.h"

namespace renderer {

OspDevice::OspDevice(DeviceKind device_kind) {
	m_kind = device_kind;


	std::printf("Device: Setting up device:\n");
	switch (device_kind) {
		case OSP_CPU:
			std::printf("    Selected device kind: [CPU]\n");
			ospLoadModule("cpu");
			m_device = ospNewDevice("cpu");
			break;
		case OSP_GPU:
			std::printf("    Selected device kind: [GPU]\n");

			ospLoadModule("gpu");
			m_device = ospNewDevice("gpu");
			break;
		default:
			std::printf("    ERROR: Renderer::setup_device. Invalid device kind given\n");
			break;
	}

	if (!m_device) {
		std::printf("    ERROR: Renderer::setup_device. Unable to register device\n");
	}
	
	std::printf("    Committing device\n");
	(void) ospDeviceCommit(m_device);
	
	std::printf("    Setting device\n");
	(void) ospSetCurrentDevice(m_device);

	std::printf("    Retaining device\n");
	(void) ospDeviceRetain(m_device);

	std::printf("    Done.\n");
}

// Release this device
void OspDevice::release() {
	ospDeviceRelease(m_device);
}

// Destructor
OspDevice::~OspDevice() {
}

} // renderer namespace
