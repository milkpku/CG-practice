#ifndef LIGHT
#define LIGHT

#include <math.h>
#include <glm.hpp>
#include "basic.h"

color reflect_model(float theta, float delta, object* obj,  light* L)
{
	reflectColor = color(0,0,0);
	// phong model
	reflectColor += theta * obj->mat.kd * obj->mat.Cd * L->c;
	// high light
	reflectColor += pow(delta,obj->mat.spec_s) * obj->mat.ks * obj->mat.Cs * L->c;
	
	return reflectColor;
}

class point_light:public light
{
	public:
		vec3 loc;
		point_light(vec3 location, float I, color c):light(I, c),loc(location){};
		
		ray generateShadowRay(vec3 dest)
		{
			return ray(dest, this->loc);
		};
		
		color calcLocalColor(scen & s, intersect_point & p)
		{
			color localColor = color(0,0,0);
			
			ray shadowRay = this->generateShadowRay(p.loc);
			
			if (dot(p.norm, shadowRay.dir)<=0)
				return localColor;
				
			intersect_point* new_p = s.intersect(shadowRay);
			if (new_p==NULL)
			{
				float theta = dot(p.norm, shadowRay.dir)；
				float delta = dot(p.ref_spec, shadowRay.dir);
				localColor = reflect_model(theta, delta, p->obj,  this);
			}	
		}
}


class dire_light:public light
{
	public:
		vec3 dir;
		dire_light(vec3 direction, color c):light(c),dir(direction){};
		
		ray generateShadowRay(vec3 dest)
		{
			// reverse the direction of light since the light has been reversed
			return ray(dest, dest - this->dir);
		};
		
		color calcLocalColor(intersect_point & p)
		{
			color localColor = color(0,0,0);
			
			ray shadowRay = this->generateShadowRay(p.loc);
			
			if (dot(p.norm, shadowRay.dir)<=0)
				return localColor;

			intersect_point* new_p = s.intersect(shadowRay);
			if (new_p==NULL)
			{
				float theta = dot(p.norm, shadowRay.dir)；
				float delta = dot(p.ref_spec, shadowRay.dir);
				localColor = reflect_model(theta, delta, p->obj,  this);
			}
		}
}

class ambient_light:public light
{
	public:
		ambient_light(color c):light(c){};
		
		ray generateShadowRay(vec3 dest)
		{
			return ray();
		};
		
		color calcLocalColor(intersect_point & p)
		{
			return p.ka*this->c;
		}
}


#endif