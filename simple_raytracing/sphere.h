#ifndef SPHERE_H
#define SPHERE_H

#include <math>
#include <glm.hpp>
#include "basic.h"
using namespace glm

namespace CG_practice{

class sphere: public object
{
	protected:
		vec3 center;
		float r;
	
	public:
		sphere(vec3 c, float radius, material m):center(c), r(radius), object(m){};
		
		intersect_point* intersect(ray r)
		{
		}
}

}

#endif