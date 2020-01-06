#pragma once

#include <Windows.h>
#include <gl/glut.h>

#include <gl/glaux.h>

#include "vec3.h"
#define TIMESQ 500

class CEnemy

{
public:
	CEnemy(void);
	~CEnemy(void);
	CEnemy(float x, float y, float z,int num,int* Score);
	int isCollision;
	int isReset;
	void draw(float tx, float ty, float tz);
	int* Score;

private:
	float px;
	float py;
	float pz;
	int r;
	int time;
	vec3 dir;
	int num;
	
};

