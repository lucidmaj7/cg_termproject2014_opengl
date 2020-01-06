#include "Enemy.h"
#include <stdio.h>
#include "vec3.h"
#include <time.h>

CEnemy::CEnemy(void)
{



}

CEnemy::CEnemy(float x, float y, float z,int num,int* Score)
{
	this->Score=Score;
	this->px=x;
	this->isReset=1;
	this->py=y;
	this->pz=z;
	dir.v[0]=px;
	dir.v[1]=py;
	dir.v[2]=pz;
	dir=unitVECTOR(dir);
	r=0;
	isCollision=0;
	time=TIMESQ;
	this->num=num;
	//this->coindrawfunc=*func();
}

CEnemy::~CEnemy(void)
{
}


void CEnemy::draw(float tx, float ty, float tz)
{

	/*
	 들어온 타겟지점과 현재 내위치의 벡터를 구해야함.


	*/
	/*
if(time==0)
{
	dir.v[0]=px-tx;
	dir.v[1]=py-ty;
	dir.v[2]=py-tz;
	dir=unitVECTOR(dir);
	time=TIMESQ;
	px=-(1/dir.v[0])*10;
	//px=-dir.v[0]*10;
//	py=-dir.v[1]*10;
//	pz=-dir.v[2]*10;
	//printf("적이동");
}else
{

	px=-(1/dir.v[0])*10;
//	py=-dir.v[1]*10;
//	pz=-dir.v[2]*10;
	time--;
	printf("%d\n",time);
}
*/
	glPushMatrix();
	//glColor3f(1.0,0,0);
		if(r==360)
			r=0;

		if(px>300||py>300||pz>300)
		{
		//	srand((unsigned) time(NULL));
			isReset=1;
			px=-(-300 + (int)(600 * rand() / (RAND_MAX + 1.0)));
			//py=rand()%300;
			py=-(-300 + (int)(600 * rand() / (RAND_MAX + 1.0)));
			pz= -(-300 + (int)(600 * rand() / (RAND_MAX + 1.0)));
			isCollision=0;
	//		printf("%f %f %f \n",px,py,pz);
		}	
		//px=px+0.1;
		//py=py-0.1;
		pz=pz+0.1;
		//r-=1;

		if(
			tx-45<px&&px<tx+45&&
			ty-15<py&&py<ty+15&&
			tz-20<pz&&pz<tz+20 &&isCollision==0
			)
			{
				printf("%d번 장애물 충돌!!!!!!!!\n",this->num);
				//if(isCollision=!1)
					isCollision++;
					isReset=0;
					(*Score)++;
			}
		
		//printf("tz: %f pz %f\n",tz,pz);

		glTranslatef(px,py,pz);
		//printf("%f %f %f \n",px=-dir.v[0],py=-dir.v[1],pz,py=-dir.v[2],pz);
		glRotatef(r+=1,1,1,0);
		if(isCollision==0)
			glutSolidCube(3);
		else
			glutSolidSphere(10,10,10);

	//	void* coindrawfunc();
	//	glutSolidCube(5);
		
	glPopMatrix();

}
