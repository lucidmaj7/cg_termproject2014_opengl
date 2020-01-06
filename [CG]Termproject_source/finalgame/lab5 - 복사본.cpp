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



GLfloat mat_amb[4]={0.1, 0.1, 0.1, 0.1};	// �ֺ����� ���� �ݻ簪
GLfloat mat_dif[4]={0.6, 0.2, 0.6, 0.0};	// �л걤�� ���� �ݻ簪
GLfloat mat_spc[4]={0.8, 0.2, 0.8, 0.5};	// �ݻ籤�� ���� �ݻ簪
GLfloat mat_emi[4]={0.1,0.1, 0.0, 0.0};	// �߱���
GLfloat mat_shi[1]={0.0};	// ����

GLfloat mat_emi_sun[4]={1.0,0.1, 0.0, 0.0};	// �¾� �߱���
GLfloat mat_emi_other[4]={0.0,0.0, 0.0, 0.0};	// �¾��̿��� emission��
GLfloat mat_dif_sun[4]={0.4, 0.1, 0.3, 0.0};	// �¾� �л걤�� ���� �ݻ簪
GLfloat mat_dif_mercury[4]={0.2, 0.1, 0.7, 0.0};	// ���� �л걤�� ���� �ݻ簪
GLfloat mat_dif_venus[4]={0.5, 0.1, 0.2, 0.0};	// �ݼ��л걤�� ���� �ݻ簪
GLfloat mat_dif_earth[4]={0.2, 0.4, 0.2, 0.0};	// ���� �л걤�� ���� �ݻ簪
GLfloat mat_dif_mars[4]={0.8, 0.4, 0.2, 0.0};	// ȭ�� �л걤�� ���� �ݻ簪
GLfloat mat_dif_saturn[4]={0.8, 0.5, 0.5, 0.0};	// �伺 �л걤�� ���� �ݻ簪
GLfloat mat_dif_jupiter[4]={0.1, 0.2, 0.7, 0.0}; // ��
GLfloat mat_dif_uraus[4]={0.5, 0.2, 0.7, 0.0}; // �伺����
GLfloat mat_dif_neptune[4]={0.1, 0.1, 0.8, 0.0}; // �伺�� ����.
/*
 *	���� �ʱ�ȭ
 */

//GLfloat *v;

CASEMODEL model,model2,model3;


void init_light(void)
{

// ���� �ʱ�ȭ
	
	static GLfloat lit_amb[4]={1.0, 1.0, 1.0, 0.0};	// �ֺ����� ����
	static GLfloat lit_dif[4]={1.0, 1.0, 1.0, 0.0}; // �л걤�� ����
	static GLfloat lit_spc[4]={1.0, 1.0, 1.0, 0.0};	// �ݻ籤�� ����
	static GLfloat lit_pos[4]={1000, 100000, 10000, 0};// ������ ��ġ



	glLightfv(GL_LIGHT0, GL_AMBIENT, lit_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lit_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lit_spc);
	glLightfv(GL_LIGHT0, GL_POSITION, lit_pos);

	// ���� ON
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

void reshape (int w, int h) {

	float ratio = w/(float)h;
	glViewport (0,0,w,h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	gluPerspective (45,ratio,0.1,10000); //�þ߰�, ������Ⱦ��, �ּ�,�ִ�Ÿ�

}

void drawPlanet()
{

	 	//��������.
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
	//����Ű�� �����̸� ����� ��ġ�� ������ �ٲ۴�.
	gluLookAt( LookAt_viewrPos_x, LookAt_viewrPos_y,  LookAt_viewrPos_z, 
			LookAt_viewerDir_x, LookAt_viewerDir_y,LookAt_viewerDir_z , 
			0, 1, 0);
	
	glScalef (2,2,1);
	

	revolutionEarth_y+=0.005f;// A�� ���� B�� ���� ����
	rotationEarth_y+=0.7f; // B�� ���� 
	


	drawPlanet(); //�༺ �׸���.

	glFlush();
}



void spckeycallback(int key, int x, int y)
{ //Ű���� �ݹ��Լ� 
// ī�޶��� ��ġ�� ��ȭ��Ų��.
	
	printf("%d ",key);
	if(key==100){ //�����̵�
		LookAt_viewrPos_x-=5.0f;
		LookAt_viewerDir_x-=5.0f;
	}
	if(key==102){ //������ �̵�
		LookAt_viewrPos_x+=5.0f;
		LookAt_viewerDir_x+=5.0f;
	}
	if(key==103){ // ������ �̵�
		LookAt_viewrPos_z+=5.0f;
		LookAt_viewerDir_z+=5.0f;
	}
	if(key==101){  // �ڷ� �̵�.
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
		printf("�������̵�\n");
		// LookAt_viewrPos_x
			LookAt_viewrPos_x+=5.0f;
			LookAt_viewerDir_x+=5.0f;
	}
	if(x<center_x)
	{
		printf("�����̵�\n");
			LookAt_viewrPos_x-=5.0f;
			LookAt_viewerDir_x-=5.0f;
	}
		if(y<center_y)
	{
		printf("�Ʒ��̵�\n");
		LookAt_viewrPos_y-=5.0f;
		LookAt_viewerDir_y-=5.0f;
	}
			if(y>center_y)
	{
		printf("���̵�\n");
		LookAt_viewrPos_y+=5.0f;
		LookAt_viewerDir_y+=5.0f;
	}



}
int main(int argc, char** argv)
{

	 revolutionEarth_y=1.0f; //�ʱ�ȭ
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
	glutCreateWindow ("Lab5-200802201������");


	glutDisplayFunc (display);
	glutIdleFunc(display);
	glutSpecialFunc(spckeycallback);
	glutReshapeFunc (reshape);//â�� ũ�Ⱑ ���Ҷ� ����
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