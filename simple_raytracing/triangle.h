#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <math>
#include <glm.hpp>
#include "basic.h"
using namespace glm

namespace CG_practice{

class triangle: public object
{
	protected:
		vec3 A, B, C;
		vec3 norm;

	public:
		triangle(vec3 A, vec3 B, vec3 C, material m):A(A), B(B), C(C), object(m)
		{
			this->norm = normalize(cross(B-A, C-B));
		};
		
		intersect_point* intersect(ray r)
		{
			// origin + t* dir lay in the plane ABC
			float k = dot(norm, ray.dir);
			if (k == 0)
				return NULL;
			
			float b = dot(norm, (ray.origin - A));
			
			float t = k/b;
			
			if (t<=0)
				return NULL;
			
			intersect_point* p = new intersect_point;
			p.norm = this->norm;
			p.spec = reflect(r.dir,this->norm);
			p.loc = ray.origin + t * ray.dir;
			p.depth = t;
			p.obj = this;
			
			return p;
		};
}

}

#endif