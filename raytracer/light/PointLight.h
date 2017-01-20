#ifndef __POINTLIGHT__
#define __POINTLIGHT__

#include "../utility/Vec3.h"

class PointLight {
public:
	Vec3 point;
	Vec3 color;
	float intensity;

	PointLight(Vec3 p, Vec3 c, float i);
};

#endif
