#include "EnemyMgr.h"
#include <stdlib.h>
#include <time.h>
CEnemyMgr::CEnemyMgr(void)
{


}

CEnemyMgr::CEnemyMgr(int n,int* Score)
{
	this->Score=Score;
	enemys=EList();
	this->collisionScore=0;
	srand((unsigned) time(NULL));
	for(int i=0;i<n; i++)
	{
	//	CEnemy a;
		 int a = -(-300 + (int)(600 * rand() / (RAND_MAX + 1.0)));
		 int b = -(-300 + (int)(600 * rand() / (RAND_MAX + 1.0)));//rand()%300;
		 int c =  -(-300 + (int)(600 * rand() / (RAND_MAX + 1.0)));
		// printf("%d ",a);
		enemys.push_back(CEnemy(a,b,c,i,Score));
	}

}

CEnemyMgr::~CEnemyMgr(void)
{
}


void CEnemyMgr::draw(float vX, float vY, float vZ)
{
	
	
	for(int i=0;i< enemys.size(); i++)
	{
		
		enemys.at(i).draw(vX, vY, vZ); //목표지점 포지션..
		
	}


}
