#pragma once
#include <cmath>
#define RADIAN_F(DEGREE) ((3.141592f * DEGREE) / 180.0f)
#ifndef _INC_GL
#include "ASEMODEL.h"
#include <Windows.h>

#include <gl\glut.h>

#include <gl\GL.h>
#include <gl\GLU.h>

#endif
//Âü°í :http://kgw1988.blog.me/90174514597

class CGLCamera
{
public:
	CGLCamera(void);
	~CGLCamera(void);
	
	 void DrawGLScene();

	// GLfloat R[3][3];



private:


	GLfloat pos[3];
	GLfloat lookAt[3];
	GLfloat upVec[3];
	GLfloat R[3][3];

	GLfloat lookVec[3];
	GLfloat leftVec[3];

	void LookVec();
	void LeftVec();




public:
		float yawAngle;
	float pitchAngle;
	void MoveLeft(void);
	void MoveRight(void);
	void MoveUp(void);
	void MoveDown(void);
	//void MoveMouseRotation(void);

private:
	void rotMatrix(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
public:
	void MoveMouseRotate(int m_x, int m_y,int x, int y);
	GLfloat* GetLookAtVec(void);
	CASEMODEL myCHAR;
	float cTheta;
	float sTheta;
	GLfloat aa[3];
};

