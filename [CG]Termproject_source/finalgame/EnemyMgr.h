#pragma once

#include <vector>
#include "Enemy.h"

typedef std::vector<CEnemy> EList;

class CEnemyMgr
{
public:
	CEnemyMgr(int n,int* Score);
	CEnemyMgr(void);
	~CEnemyMgr(void);
	int collisionScore;
	int *Score;
private:
	int numOfEnemy;
	EList enemys;
	
public:
	void draw(float vX, float vY, float vZ);
};

