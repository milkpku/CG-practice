#ifndef RAY_TRACE
#define RAY_TRACE

#include <math.h>
#include <glm.hpp>
#include "basic.h"
#include "light.h"

color RayTrace(scen & s, ray & r)
{
	color c = scen.backgroundColor;
	
	intersect_point* p = s.intersect(r);
	if (p!=NULL)
	{
		c = RayShade(s, *p);
		// if p->obj->mat.is_ref
		// if p->obj->mat.is_trans
	}
}

color RayShade(scen & s, intersect_point & p)
{
	color localColor = (0,0,0);
	if (s.ambient != NULL)
		localColor = s.ambient->c;
		
	for(int i=0; i<sizeof(s.lights); i++)
	{
		ray shadowRay = s.ligths[i]->generateShadowRay(p.loc);
		intersect_point* new_p = s.intersect(shadowRay);
		if (new_p==NULL)
			localColor += s.ligths[i].calcLocalColor(s, *p);	
	}
	return localColor;
}

#endif