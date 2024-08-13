#pragma once
#include "defines.h"
#include "osp.inl"

namespace renderer {

// Types of devices we support for rendering with ospray
enum DeviceKind {
	OSP_CPU, 
	OSP_GPU
};

class OspDevice {
public:
	OspDevice(DeviceKind device_kind);
	~OspDevice();

	void release();

	inline DeviceKind kind() { return m_kind; }
private:
	DeviceKind m_kind;
	OSPDevice m_device;
};

}
