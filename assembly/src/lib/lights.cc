#include "lights.h"
#include "osp.inl"
#include <cstdio>

namespace renderer {
namespace light {

void SunSky::_setup_light() {
	return;
}

void Ambient::_setup_light() {
	std::printf("Creating Ambient light...\n");
	this->m_light = ospNewLight("ambient");

	std::printf("    Commiting.\n");
	ospCommit(m_light);
	
	std::printf("    Adding to world.\n");
	ospSetObjectAsData(m_world, "light", OSP_LIGHT, m_light);
	
	std::printf("    Releasing.\n");
	ospRelease(m_light);
	
	std::printf("    Committing world.\n");
	ospCommit(m_world);

	std::printf("    Done");
}

} // light namespace
} // renderer namespace
