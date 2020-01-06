#include "vec3.h"


float sizeofvec3(vec3 v)
{
	return sqrt(pow(v.v[0],2)+pow(v.v[1],2)+pow(v.v[2],2)+0);

}


vec3 unitVECTOR(vec3 v)
{
	//vec3 u;
	float t =(float)sizeofvec3(v);

	for(int i=0;i<3;i++)
		v.v[i]=v.v[i]/t;


	return v;

	
}
