#pragma once

#include "defines.h"
#include "osp.inl"

namespace renderer {

namespace light {

// Interface and structure for a Light object in ospray
class Light {
public:
protected:
	OSPWorld m_world;
	rkcommon::math::vec3f m_color;
	float m_intensity;
	bool m_visible;
	OSPLight m_light;

	virtual void _setup_light() = 0;
};

// Sunsky light 
class SunSky : public Light {
public:
	
	SunSky(
		OSPWorld world,
		rkcommon::math::vec3f color, 
		float intensity, 
		uint intensityQuantity, 
		bool visible,
		rkcommon::math::vec3f up,
		rkcommon::math::vec3f direction,
		float turbidity = 3,
		float albedo = 0.3,
		float horizonExtension = 0.01
	)
	: m_world(world),
	  m_color(color),
	  m_intensity(intensity),
	  m_visible(visible)
	{
		_setup_light();
	}

	~SunSky() {
	}
private:
	OSPWorld m_world;
	rkcommon::math::vec3f m_color;
	float m_intensity;
	bool m_visible;
	OSPLight m_light;
	
	rkcommon::math::vec3f m_up;
	rkcommon::math::vec3f m_direction;
	float m_turbidity;
	float m_albedo;
	

protected:
	void _setup_light() override;
};

// Ambient light
class Ambient : public Light {
public:
	Ambient(
		OSPWorld world,
		rkcommon::math::vec3f color, 
		float intensity, 
		uint intensityQuantity, 
		bool visible
	)
	: m_world(world),
	  m_color(color),
	  m_intensity(intensity),
	  m_visible(visible)
	{
		_setup_light();
	}

	~Ambient() {}
private:
	OSPWorld m_world;
	rkcommon::math::vec3f m_color;
	float m_intensity;
	bool m_visible;
	OSPLight m_light;

protected:
	void _setup_light() override;
};

} // light namespace
} // renderer namespace
