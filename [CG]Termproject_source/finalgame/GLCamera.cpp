
#include "GLCamera.h"


CGLCamera::CGLCamera(void)
{

	pos[0] = 0.f;
	pos[1] = 0.f;

	pos[2] = 0100.f;

	lookAt[0] = 0.f;

	lookAt[1] = 0.f;

	lookAt[2] = 090.f;

	upVec[0] = 0.f;

	upVec[1] = 1.f;

	upVec[2] = 0.f;
//	myCHAR=CASEMODEL("55.ASE");
}



void CGLCamera::LookVec()
{
	lookVec[0] = lookAt[0] - pos[0];

	lookVec[1] = lookAt[1] - pos[1];

	lookVec[2] = lookAt[2] - pos[2];

	aa[0]=lookVec[0];
	aa[1]=lookVec[1];
	aa[2]=lookVec[2];;

	//단위벡터화

	GLfloat root = sqrt(lookVec[0]*lookVec[0] + lookVec[1]*lookVec[1] + lookVec[2]*lookVec[2]);

	lookVec[0] = lookVec[0] / root;

	lookVec[1] = lookVec[1] / root;

	lookVec[2] = lookVec[2] / root;





}

void CGLCamera::LeftVec()
{
	LookVec();//lookVec설정

	leftVec[0] = ( upVec[1] * lookVec[2] ) - ( upVec[2] * lookVec[1] );

	leftVec[1] = ( upVec[2] * lookVec[0] ) - ( upVec[0] * lookVec[2] );

	leftVec[2] = ( upVec[0] * lookVec[1] ) - ( upVec[1] * lookVec[0] );

	//단위벡터화

	GLfloat root = sqrt(leftVec[0]*leftVec[0] + leftVec[1]*leftVec[1] + leftVec[2]*leftVec[2]);

	leftVec[0] = leftVec[0] / root;

	leftVec[1] = leftVec[1] / root;

	leftVec[2] = leftVec[2] / root;




}


CGLCamera::~CGLCamera(void)
{
}


void CGLCamera::DrawGLScene()
{
	gluLookAt(pos[0],pos[1],pos[2], lookAt[0], lookAt[1], lookAt[2], upVec[0], upVec[1], upVec[2]);
//	myCHAR.drawASE();
}

void CGLCamera::MoveLeft(void)
{
	LeftVec();
	
	for(int i = 0; i < 3; i++){

		pos[i] += leftVec[i];

		lookAt[i] += leftVec[i];

	}
	

	//MoveMouseRotate(0, 0,1, 0);
}


void CGLCamera::MoveRight(void)
{
	LeftVec();

	for(int i = 0; i < 3; i++){

		pos[i] -= leftVec[i];

		lookAt[i] -= leftVec[i];

	}





}


void CGLCamera::MoveUp(void)
{
	LookVec();

	for(int i = 0; i < 3; i++){

		pos[i] += lookVec[i];

		lookAt[i] += lookVec[i];

	}




}


void CGLCamera::MoveDown(void)
{
	LookVec();
	
	for(int i = 0; i < 3; i++){

		pos[i] -= lookVec[i];

		lookAt[i] -= lookVec[i];

	}




}

void CGLCamera::rotMatrix(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{

	float cosTheta = (float)cos(angle);

  float sinTheta = (float)sin(angle);
 //cTheta=cosTheta;
  //sTheta=sinTheta;
 

  // Find the new x position for the new rotated point 

  R[0][0] = ((1 - cosTheta) * x * x + cosTheta);

  R[0][1] = ((1 - cosTheta) * x * y - sinTheta * z);

  R[0][2] = ((1 - cosTheta) * x * z + sinTheta * y);



  // Find the new y position for the new rotated point

  R[1][0] = ((1 - cosTheta) * x * y + sinTheta * z);

  R[1][1] = ((1 - cosTheta) * y * y + cosTheta);

  R[1][2] = ((1 - cosTheta) * y * z - sinTheta * x);

 

  // Find the new z position for the new rotated point

  R[2][0] = ((1 - cosTheta) * x * z - sinTheta * y);

  R[2][1] = ((1 - cosTheta) * y * z + sinTheta * x);

  R[2][2] = ((1 - cosTheta) * z * z + cosTheta);
}


void CGLCamera::MoveMouseRotate(int m_x, int m_y,int x, int y)
{

//	CPoint p;
	//GetCursorPos(&p);

	GLfloat Angle = 0;
	GLfloat V_[3] = { 0, 0, 0 };
	GLfloat V__[3] = { 0, 0, 0 };

	//Yaw		
	LookVec();
	
	Angle = ( m_x - x ) * 0.01;
//	yawAngle=( m_x - x ) * 0.01;
	rotMatrix(Angle, 0, 1, 0);
	//printf("angle %f \n",Angle);
	//printf("Yaw: angle : %lf\n",Angle);	
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++)
			V_[i] += R[i][j] * lookVec[j];
		//V_[i] += R[i][j] * lookVec[j];
	}
		
	//pitch
	Angle = (y - m_y ) * 0.01;
//	pitchAngle=(y - m_y ) * 0.01;
	LeftVec();

	rotMatrix(Angle, leftVec[0], leftVec[1], leftVec[2]);
		
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++)
			V__[i] += R[i][j] * V_[j];
	}
		
	for(int i = 0; i < 3; i++)
		lookAt[i] = pos[i] + V__[i];
}


GLfloat* CGLCamera::GetLookAtVec(void)
{
	
	return this->lookAt;
}
