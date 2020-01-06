//#include <gl/glu.h>


//#include <Windows.h>


#include "ASEMODEL.h"

float revolutionEarth_y;
float rotationEarth_y;

double LookAt_viewrPos_x;
double LookAt_viewrPos_y;
double LookAt_viewrPos_z;


double LookAt_viewerDir_x;
double LookAt_viewerDir_y;
double LookAt_viewerDir_z;



GLfloat mat_amb[4]={0.1, 0.1, 0.1, 0.1};	// 주변광에 대한 반사값
GLfloat mat_dif[4]={0.6, 0.2, 0.6, 0.0};	// 분산광에 대한 반사값
GLfloat mat_spc[4]={0.8, 0.2, 0.8, 0.5};	// 반사광에 대한 반사값
GLfloat mat_emi[4]={0.1,0.1, 0.0, 0.0};	// 발광값
GLfloat mat_shi[1]={0.0};	// 광택

GLfloat mat_emi_sun[4]={1.0,0.1, 0.0, 0.0};	// 태양 발광값
GLfloat mat_emi_other[4]={0.0,0.0, 0.0, 0.0};	// 태양이외의 emission값
GLfloat mat_dif_sun[4]={0.4, 0.1, 0.3, 0.0};	// 태양 분산광에 대한 반사값
GLfloat mat_dif_mercury[4]={0.2, 0.1, 0.7, 0.0};	// 수성 분산광에 대한 반사값
GLfloat mat_dif_venus[4]={0.5, 0.1, 0.2, 0.0};	// 금성분산광에 대한 반사값
GLfloat mat_dif_earth[4]={0.2, 0.4, 0.2, 0.0};	// 지구 분산광에 대한 반사값
GLfloat mat_dif_mars[4]={0.8, 0.4, 0.2, 0.0};	// 화성 분산광에 대한 반사값
GLfloat mat_dif_saturn[4]={0.8, 0.5, 0.5, 0.0};	// 토성 분산광에 대한 반사값
GLfloat mat_dif_jupiter[4]={0.1, 0.2, 0.7, 0.0}; // 목성
GLfloat mat_dif_uraus[4]={0.5, 0.2, 0.7, 0.0}; // 토성위성
GLfloat mat_dif_neptune[4]={0.1, 0.1, 0.8, 0.0}; // 토성의 위성.
/*
 *	광원 초기화
 */

//GLfloat *v;

CASEMODEL model,model2,model3;


void init_light(void)
{

// 광원 초기화
	
	static GLfloat lit_amb[4]={1.0, 1.0, 1.0, 0.0};	// 주변광의 강도
	static GLfloat lit_dif[4]={1.0, 1.0, 1.0, 0.0}; // 분산광의 강도
	static GLfloat lit_spc[4]={1.0, 1.0, 1.0, 0.0};	// 반사광의 강도
	static GLfloat lit_pos[4]={1000, 100000, 10000, 0};// 광원의 위치



	glLightfv(GL_LIGHT0, GL_AMBIENT, lit_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lit_spc);
	glLightfv(GL_LIGHT0, GL_POSITION, lit_pos);

	// 광원 ON
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

void reshape (int w, int h) {

	float ratio = w/(float)h;
	glViewport (0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	gluPerspective (45,ratio,0.1,10000); //시야각, 가로종횡비, 최소,최대거리

}

void drawPlanet()
{

	 	//재질세팅.
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spc);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shi);		
				model.drawASE();
		glRotatef(revolutionEarth_y,0,1,0);
		
			//glEnable (GL_TEXTURE_2D);
		
		
	
		model2.drawASE();
	model3.drawASE();

	SetCursorPos(640/2,480/2);
}


void display () 
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f (0.8, 0.5, 0.8);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
	init_light();
	//방향키를 움직이면 뷰어의 위치와 방향을 바꾼다.
	gluLookAt( LookAt_viewrPos_x, LookAt_viewrPos_y,  LookAt_viewrPos_z, 
			LookAt_viewerDir_x, LookAt_viewerDir_y,LookAt_viewerDir_z , 
			0, 1, 0);
	
	glScalef (2,2,1);
	

	revolutionEarth_y+=0.005f;// A의 자전 B의 공전 증가
	rotationEarth_y+=0.7f; // B의 자전 
	


	drawPlanet(); //행성 그리기.

	glFlush();
}



void spckeycallback(int key, int x, int y)
{ //키보드 콜백함수 
// 카메라의 위치를 변화시킨다.
	
	printf("%d ",key);
	if(key==100){ //왼쪽이동
		LookAt_viewrPos_x-=5.0f;
		LookAt_viewerDir_x-=5.0f;
	}
	if(key==102){ //오른쪽 이동
		LookAt_viewrPos_x+=5.0f;
		LookAt_viewerDir_x+=5.0f;
	}
	if(key==103){ // 앞으로 이동
		LookAt_viewrPos_z+=5.0f;
		LookAt_viewerDir_z+=5.0f;
	}
	if(key==101){  // 뒤로 이동.
		LookAt_viewrPos_z-=5.0f;
			LookAt_viewerDir_z-=5.0f;
	}

}
void mousecallback(int btn, int state, int x, int y)
{
	printf("%d %d %d %d \n",btn,state,x,y);
}
void passivemousecallback(int x, int y)
{

	int center_x=640/2;
	int center_y=480/2;

	printf(" %d %d \n",x,y);

	if(x>center_x)
	{
		printf("오른쪽이동\n");
		// LookAt_viewrPos_x
			LookAt_viewrPos_x+=5.0f;
			LookAt_viewerDir_x+=5.0f;
	}
	if(x<center_x)
	{
		printf("왼쪽이동\n");
			LookAt_viewrPos_x-=5.0f;
			LookAt_viewerDir_x-=5.0f;
	}
		if(y<center_y)
	{
		printf("아래이동\n");
		LookAt_viewrPos_y-=5.0f;
		LookAt_viewerDir_y-=5.0f;
	}
			if(y>center_y)
	{
		printf("위이동\n");
		LookAt_viewrPos_y+=5.0f;
		LookAt_viewerDir_y+=5.0f;
	}



}
int main(int argc, char** argv)
{

	 revolutionEarth_y=1.0f; //초기화
	 rotationEarth_y=7.0f;
	 LookAt_viewrPos_x=10;
	 LookAt_viewrPos_y=40;
	 LookAt_viewrPos_z=500;
	 LookAt_viewerDir_x=0;
	 LookAt_viewerDir_y=0.3;
	 LookAt_viewerDir_z=0;
	 //load_ase();

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE|GLUT_RGB);

	glutInitWindowSize (640, 480);
	glutCreateWindow ("Lab5-200802201정원희");


	glutDisplayFunc (display);
	glutIdleFunc(display);
	glutSpecialFunc(spckeycallback);
	glutReshapeFunc (reshape);//창의 크기가 변할때 실행
	glutMouseFunc(mousecallback); 
	glEnable(GL_DEPTH_TEST);
	glutPassiveMotionFunc(passivemousecallback);
	//glutPassiveMouseFunc();
		 char modelfile[1][100]={"input.ASE"};
	// model= CASEMODEL( modelfile[0]);
	
		 
	  model= CASEMODEL("2.ASE"); 
	  model2=CASEMODEL("3.ASE");
	  model3=CASEMODEL("4.ASE");

	glutMainLoop ();

	return 0;

}