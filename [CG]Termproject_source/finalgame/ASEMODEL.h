

#pragma once
#include <stdlib.h>
#include <gl/glut.h>
#include <stdio.h>
#include <gl/glaux.h>
#include <string.h>
class CASEMODEL
{
	typedef struct _VERTEX{
	GLfloat v[4];

}VERTEX,*PVERTEX;

typedef struct _NORMAL{
	float x;
	float  y;
	float  z;
}NORMAL,*PNORMAL;

typedef struct _FACE{

	GLfloat v[3][3];
	GLfloat n[3][3];
	
	int vertexnum[3];

}FACE, *PFACE;

typedef struct _TFACE{

	
	int tvertnum[3];
}TFACE, *PTFACE;

public:
	CASEMODEL(void);
	CASEMODEL(char* filename);
	~CASEMODEL(void);
	
	void drawASE();

private:
	void loadASE(char* filename);
	void textureinit(void);

	int vertexNUM,faceNUM,tvertexNum, tfaceNum;
	PFACE face;
	PTFACE tface;
	PVERTEX v;
	PVERTEX n;
	PVERTEX t;///////
	
	GLfloat mat_amb[4];	// 주변광에 대한 반사값
	GLfloat mat_dif[4];	// 분산광에 대한 반사값
	GLfloat mat_spc[4];	// 반사광에 대한 반사값
	wchar_t bitmap[100];
	unsigned int ids[2];
	AUX_RGBImageRec *tex[2];
	wchar_t file[100];
};

