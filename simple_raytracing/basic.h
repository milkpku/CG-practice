#ifndef BASIC
#define BASIC

#include <glm.hpp>
#include <math.h>

using namespace glm

namespace CG_practice{

typedef vec3 color

class ray
{
	public:
		vec3 origin;		// origin of ray
		vec3 dir;			// direction of ray
		void norm(){this->dir /= sqrt(dot(this->dir, this->dir));};
		ray(){};
		// generate from origin to destination
		ray(vec3 origin, vec3 dest):origin(origin){this->dir = dest - origin; this->norm();};
}

struct intersect_point
{
	vec3 loc;				// where ray intersect with object
	vec3 norm;				// the normal vector of intersected surface
	vec3 ref_spec;			// perspective ray reflected by surface normal
	float depth; 			// length between ray.origin and loc
	object* obj;			// object ray intersects
}

struct material
{
	bool is_trans; 		// is transparent
	bool is_ref;		// is reflective
	color Cd, Cs;		// color of diffuse layer | specular layer
	float ka, kd		// efficiency of diffuse layer reflecting ambient light | direction light 
	float ks;   		// efficiency of specular layer reflecting direction light
	float spec_s;		// specular power coefficient
}

class object
{
	public:
		material mat;
		object(material m):mat(m){};
		virtual intersect_point* intersect(ray r);
}

class light
{
	public:
		color c;
		light(float intense, color col):I(intense), c(col){};
		virtual ray generateShadowRay(vec3 dest)
		virtual color calcLocalColor(intersect_point & p);
}

class scen
{
	protected:
		object* obj;
		scen* subsecn;
		light* lights;
		light* ambient;
		color backgroundColor;
	public:
		intersect_point* intersect(ray r);
}

class cameral
{
	public:
		vec3* loc;
		ray* dir;
		float angle, cull_near, cull_far;
}

class window
{
	protected:
		cameral* cam;
		scen* main_scen;
	public:
		void render(FILE* output);
}
	
}
#endif