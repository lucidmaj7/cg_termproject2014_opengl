//#include <gl/glu.h>
#pragma once


//#include <Windows.h>

//#include <Windows.h>
#include "ASEMODEL.h"
#include "GLCamera.h"
#include "vec3.h"
#include "EnemyMgr.h"
#include <string>
char FSMode[200] ="1920x1080:32@60";
#define WINSIZEX 800	
#define WINSIZEY 600 
float revolutionEarth_y;
float rotationEarth_y;
float plane_rotate_Z=0;
float plane_rotate_Y=0;
float plane_rotate_X=0;

float plane_pos_x;
float plane_pos_y;
float plane_pos_z;
float planev_lookatv_ratio;
CEnemyMgr emgr;
CGLCamera cam;
int Score;

MSG Msg;
UINT TimerId;
int sec=0;


double LookAt_viewrPos_x;
double LookAt_viewrPos_y;
double LookAt_viewrPos_z;


double LookAt_viewerDir_x;
double LookAt_viewerDir_y;
double LookAt_viewerDir_z;


GLfloat R[16];


GLfloat mat_amb[4]={0.5, 0.0,0.0, 0.5};	// 주변광에 대한 반사값
GLfloat mat_dif[4]={1,0.0, 0.0, 0.5};	// 분산광에 대한 반사값
GLfloat mat_spc[4]={0.7, 0.7, 0.7, 1.0};	// 반사광에 대한 반사값
GLfloat mat_emi[4]={0.0,0.0, 0.0, 0.0};	// 발광값
GLfloat mat_shi[1]={0.0};	// 광택

/*
*	광원 초기화
*/

//GLfloat *v;

CASEMODEL model,model2,model3,coinModel;


VOID CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime) {
	

	sec+=1000;
	wchar_t msg[100];
	wsprintf(msg,TEXT("당신의 점수는 %d 점입니다."),Score);
	if(sec==30*1000)
	{
		KillTimer(NULL, TimerId);
		MessageBox(NULL,msg,TEXT("게임오버"),NULL);
		exit(1);
	}

}



void drawText(const char *text, int length, int x, int y){
	glColor3f(0.0, 0.9, 0.5);
	glMatrixMode(GL_PROJECTION); // change the current matrix to PROJECTION
	double matrix[16]; // 16 doubles in stack memory
	glGetDoublev(GL_PROJECTION_MATRIX, matrix); // get the values from PROJECTION matrix to local variable
	glLoadIdentity(); // reset PROJECTION matrix to identity matrix
	glOrtho(0, 800, 0, 600, -5, 5); // orthographic perspective
	glMatrixMode(GL_MODELVIEW); // change current matrix to MODELVIEW matrix again
	glLoadIdentity(); // reset it to identity matrix
	glPushMatrix(); // push current state of MODELVIEW matrix to stack
	glLoadIdentity(); // reset it again. (may not be required, but it my convention)
	glRasterPos2i(x, y); // raster position in 2D
	for(int i=0; i<length; i++){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]); // generation of characters in our text with 9 by 15 GLU font
	}
	glPopMatrix(); // get MODELVIEW matrix value from stack
	glMatrixMode(GL_PROJECTION); // change current matrix mode to PROJECTION
	glLoadMatrixd(matrix); // reset
	glMatrixMode(GL_MODELVIEW); // change current matrix mode to MODELVIEW
}

void init_light(void)
{

	// 광원 초기화

	static GLfloat lit_amb[4]={1.0, 1.0, 1.0, 1.0};	// 주변광의 강도
	static GLfloat lit_dif[4]={1.0, 1.0, 1.0, 1.0}; // 분산광의 강도
	static GLfloat lit_spc[4]={1.0, 1.0, 1.0, 1.0};	// 반사광의 강도
	static GLfloat lit_pos[4]={500, 500,-500, 0.0};// 광원의 위치


	glLightfv(GL_LIGHT0, GL_AMBIENT, lit_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lit_spc);
	glLightfv(GL_LIGHT0, GL_POSITION, lit_pos);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambdif);
	// 광원 ON
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

void reshape (int w, int h) {

	float ratio = w/(float)h;
	glViewport (0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	gluPerspective (60,ratio,1,1000); //시야각, 가로종횡비, 최소,최대거리

}



void drawPlanet()
{





	glPushMatrix();
	
		glTranslatef(cam.GetLookAtVec()[0],cam.GetLookAtVec()[1]-10,cam.GetLookAtVec()[2]-50);
		glRotatef(plane_rotate_Y,0,1,0);
		glRotatef(plane_rotate_Z,0,0,1);
		//printf("%f \n ",plane_rotate_Y);

		model2.drawASE();

	glPopMatrix();


	model3.drawASE();





}


void display () 
{
	/*if (Msg.message == WM_TIMER)
		sec+=1000;
	DispatchMessage(&Msg);
	*/
	init_light();
	glEnable(GL_BLEND);
	glClearColor(1,1,1,1);


	
	//  glEnable(GL_FOG);
	//glFogf(GL_FOG_MODE,GL_LINEAR);

	// SetCursorPos(640/2, 480/2); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glMatrixMode (GL_MODELVIEW);
	//	glColor3f (0.8, 1.0, 4.0);

	glLoadIdentity ();

	cam.DrawGLScene();

	glPushMatrix();
		std::string text;
		std::string s = std::to_string((LONGLONG)Score);

		text="score : "+s;
		s = std::to_string((LONGLONG)(sec/1000));
		text=text+"  time:"+s+"sec/30";
		//sprintf(text,TEXT("collision Score: %d "),emgr.collisionScore);

		drawText(text.data(), text.size(), 10, 100);
	glPopMatrix();

	drawPlanet(); 

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	
	glPushMatrix();
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spc);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  mat_dif);	

		emgr.draw(cam.GetLookAtVec()[0],cam.GetLookAtVec()[1]-15,cam.GetLookAtVec()[2]-30);


	glPopMatrix();

			
	glutWarpPointer(WINSIZEX/2,WINSIZEY/2);

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
		
	
	glFlush();
//	glutSwapBuffers();



}



void spckeycallback(int key, int x, int y)
{ //키보드 콜백함수 
	// 카메라의 위치를 변화시킨다.

	//printf("%d ",key);


	if(key==100){ //왼쪽이동

		cam.MoveLeft();
	}
	if(key==102){ //오른쪽 이동

		cam.MoveRight();
	}
	if(key==103){ // 앞으로 이동
		cam.MoveDown();
	}
	if(key==101){  // 뒤로 이동.
		cam.MoveUp();

	}

}
void mousecallback(int btn, int state, int x, int y)
{
	exit(1);
	//printf("%d %d %d %d \n",btn,state,x,y);
	//	SetCursorPos(640/2,480/2);
}


void upkeycallback(unsigned char key, int x, int y)
{
	//	printf("%d ",key);


	if(key=='a'){ //왼쪽이동
		plane_rotate_Z=0;
		//cam.MoveLeft();

	}
	if(key=='d'){ //오른쪽 이동
		plane_rotate_Z=0;
		//cam.MoveRight();
	}
	if(key=='s'){ // 앞으로 이동
		plane_rotate_Z=0;
		//cam.MoveDown();
	}
	if(key=='w'){  // 뒤로 이동.
		plane_rotate_Z=0;
		//cam.MoveUp();

	}



}


void keycallback(unsigned char key, int x, int y)
{
	printf("%d ",key);


	if(key=='a'){ 
		plane_rotate_Z=30;
		cam.MoveLeft();
	}
	if(key=='d'){
		plane_rotate_Z=-30;
		cam.MoveRight();
	}
	if(key=='s'){ 
		cam.MoveDown();
	}
	if(key=='w'){ 
		cam.MoveUp();

	}

}

void passivemousecallback(int x, int y)
{

	int center_x=WINSIZEX/2;
	int center_y=WINSIZEY/2;

	cam.MoveMouseRotate(center_x,center_y,x,y);
}



int main(int argc, char** argv)
{

	SetConsoleTitle(TEXT("dd"));



	revolutionEarth_y=1.0f; //초기화
	rotationEarth_y=7.0f;
	LookAt_viewrPos_x=10;
	LookAt_viewrPos_y=40;
	LookAt_viewrPos_z=500;
	LookAt_viewerDir_x=0;
	LookAt_viewerDir_y=0.3;
	LookAt_viewerDir_z=0;
	plane_pos_x=0;
	plane_pos_y=0;
	plane_pos_z=10;

	//load_ase();


	cam=CGLCamera();


	//glutPassiveMouseFunc();
	char modelfile[1][100]={"input.ASE"};
	// model= CASEMODEL( modelfile[0]);
	Score=0;
	TimerId = SetTimer(NULL, 0, 1000, &TimerProc);

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowPosition( 500,200);  
	glutInitWindowSize (WINSIZEX,WINSIZEY);

	glutCreateWindow ("많이 주워먹기");

	//	 glutGameModeString(FSMode);

	//if( glutGameModeGet( GLUT_GAME_MODE_POSSIBLE ) ) 
	// glutEnterGameMode(); 


	//
	//CreateThread( NULL , 0 , ThreadFunction , NULL , 0 , NULL ) ;


	glutSetCursor(GLUT_CURSOR_NONE);


	glutDisplayFunc (display);
	glutIdleFunc(display);
	glutSpecialFunc(spckeycallback);
	glutReshapeFunc (reshape);//창의 크기가 변할때 실행
	glutMouseFunc(mousecallback); 

	glutPassiveMotionFunc(passivemousecallback);
	// glEnable(GL_TEXTURE_2D);



	glutKeyboardUpFunc(upkeycallback);
	glutKeyboardFunc(keycallback);
	//model= CASEMODEL("pot.ASE"); 
	model2=CASEMODEL("3.ASE");
	model3=CASEMODEL("sky.ASE");

	
	glEnable(GL_DEPTH_TEST);


	emgr=CEnemyMgr(500,&Score);

	glShadeModel(GL_SMOOTH);
	glutWarpPointer(WINSIZEX/2,WINSIZEY/2);
	//FreeConsole();
	////////////




	/////////////


	glutMainLoop ();


	return 0;

}

