#include "ASEMODEL.h"


CASEMODEL::CASEMODEL(char* filename)
{

	
	
	 mat_amb[0]=0.1;
	 mat_amb[1]=0.1;
	 mat_amb[2]=0.1;

	 mat_amb[3]=1;
	 
	 mat_dif[0]=0.9;
	 mat_dif[1]=0.9;
	 mat_dif[2]=0.9;
	 mat_dif[3]=1;
	 
	 mat_spc[0]=0.8;
	 mat_spc[1]=0.8;
	 mat_spc[2]=0.8;
	 mat_spc[3]=1;
		//textureinit();
	 loadASE(filename);

	


}
CASEMODEL::CASEMODEL(void)
{
//	loadASE( filename);
	printf("error!!");
}

CASEMODEL::~CASEMODEL(void)
{



}


void CASEMODEL::drawASE()
{

		
		glPushMatrix();
		
		glEnable (GL_TEXTURE_2D);
		
		glBindTexture (GL_TEXTURE_2D, ids[0]);
		glBegin(GL_TRIANGLES);	
	
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spc);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);		
		
		
		for(int j=0; j<faceNUM;j++)
		{
			for(int m=0;m<3;m++)
			{

				glNormal3f(face[j].n[m][0],face[j].n[m][1], face[j].n[m][2]);
				glTexCoord2f(t[tface[j].tvertnum[m]].v[0],t[tface[j].tvertnum[m]].v[1]);
				glVertex3f(v[face[j].vertexnum[m]].v[0], v[face[j].vertexnum[m]].v[1],v[face[j].vertexnum[m]].v[2]);
			}
		 
		}
		glEnd();
			
		glDisable(GL_TEXTURE_2D);
	
		glPopMatrix();

}

void CASEMODEL::textureinit()
{
	//LPCWSTR file=TEXT("earth.bmp"); 
	
	
		tex[0]=auxDIBImageLoad(file);
	
		glGenTextures(2, &ids[0]);
	
	{
	
		wprintf(bitmap);
	
		glBindTexture (GL_TEXTURE_2D, ids[0]);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, tex[0]->sizeX, tex[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, tex[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//glEnable(GL_TEXTURE_2D);
	}
	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);

}

void CASEMODEL::loadASE(char* filename)
{
	FILE *f;
	FILE *g;
	FILE *h;
	f=fopen(filename,"r");
	//h=fopen("normal.txt","r");
	g=fopen("out.txt","w");

	
	float a,b,c;
	int d;
	int i=0;
	
	
	char buf[1000];
	 //VERTEX v[8];
	char line[256];


	int bitmapFlag=0;
	while(!feof(f))
	{
		fscanf(f,"%[^\n]\n",buf);
		//fgets(line,256,f);
		//sscanf(line,"%s",buf);
	//puts(buf);
	if(strstr(buf,"*BITMAP"))
		{
			
			if(bitmapFlag==0)
			{
			char fname[100];
			sscanf(buf,"*BITMAP \"%s\"\n",fname);
			//wchar_t des[100];
			  int nLen = ( int )strlen( fname )-1;
			  fname[nLen]='\0';
			 mbstowcs( file, fname, nLen );
			 file[nLen]='\0';
			 	textureinit();
				bitmapFlag=1;
			}

			//file=fname;

		}
		
		if(strstr(buf,"*MESH_NUMTVERTEX"))
		{
			puts(buf);
			sscanf(buf,"*MESH_NUMTVERTEX %d\n",&tvertexNum);
			t=(PVERTEX)malloc(tvertexNum*sizeof(VERTEX));


		}
		if(strstr(buf,"*MESH_TVERTLIST {"))//"*MESH_VERTEX_LIST
		{i=0;
			while(1)
			{
				fscanf(f,"%[^\n]\n",buf);
				if(strstr(buf,"}"))
					break;
				puts(buf);
				//printf("-");
				sscanf(buf,"\t\t\t*MESH_TVERT %d\t%f %f %f\n",&d,&t[i].v[0],&t[i].v[1],&t[i].v[2]);
			
				i++;

			}
		}
		if(strstr(buf,"*MESH_NUMTVFACES"))
		{
			puts(buf);
			sscanf(buf,"*MESH_NUMTVFACES %d\n",&tfaceNum);
			tface=(PTFACE)malloc(tfaceNum*sizeof(TFACE));


		}
		if(strstr(buf, "*MESH_TFACELIST {"))
		{
			while(1)
			{
				int temp[3];
				//GLfloat temp[3];
				fscanf(f,"%[^\n]\n",buf);
				if(strstr(buf,"}"))
					break;

				sscanf(buf,"\t\t\t*MESH_TFACE %d\t%d\t%d\t%d\n",&d, &temp[0],&temp[1],&temp[2]);
				tface[d].tvertnum[0]=temp[0];
				tface[d].tvertnum[1]=temp[1];
				tface[d].tvertnum[2]=temp[2];



			}

		}



		if(strstr(buf,"*MESH_NUMVERTEX"))
		{	
			puts(buf);
			sscanf(buf,"*MESH_NUMVERTEX %d\n",&vertexNUM);
			v=(PVERTEX)malloc(vertexNUM*sizeof(VERTEX));
		}
		if(strstr(buf,"*MESH_NUMFACES"))
		{
			puts(buf);
			sscanf(buf,"*MESH_NUMFACES %d\n",&faceNUM);
			n=(PVERTEX)malloc(vertexNUM*sizeof(VERTEX));
		}
		if(strstr(buf,"*MESH_VERTEX_LIST {"))//"*MESH_VERTEX_LIST
		{
			while(1)
			{
				fscanf(f,"%[^\n]\n",buf);
				if(strstr(buf,"}"))
					break;
				puts(buf);
				//printf("-");
				sscanf(buf,"\t\t\t*MESH_VERTEX %d\t%f %f %f\n",&d,&v[i].v[0],&v[i].v[2],&v[i].v[1]);
			
				i++;

			}
		}




		if(strstr(buf,"*MATERIAL_AMBIENT"))
		{
			sscanf(buf,"*MATERIAL_AMBIENT %f %f %f\n",&mat_amb[0],&mat_amb[1],&mat_amb[2]);
			mat_amb[3]=1;
			
		}
		if(strstr(buf,"*MATERIAL_DIFFUSE"))
		{
			sscanf(buf,"*MATERIAL_DIFFUSE %f %f %f\n",&mat_dif[0],&mat_dif[1],&mat_dif[2]);
			mat_dif[3]=1;
			
		}
		if(strstr(buf,"*MATERIAL_SPECULAR"))
		{
			sscanf(buf,"*MATERIAL_SPECULAR %f %f %f\n",&mat_spc[0],&mat_spc[1],&mat_spc[2]);
			mat_spc[3]=1;
			
		}

		if(strstr(buf,"*MESH_NORMALS {"))
		{
			face=(PFACE)malloc(faceNUM*sizeof(FACE));
				int faceflag=-1;
			int k=-1;
			while(1)
			{
				GLfloat temp[3];
				//VERTEX temp;
			int bb=0;
		
			//fgets(buf,sizeof(100),h);
			//buf[100-1]=0;
			fscanf(f,"%[^\n]\n",buf);
				if(strstr(buf,"}"))
					break;
		//	puts(buf);
	//		puts(buf);
			
			if(strstr(buf,"*MESH_FACENORMAL"))
			{
			//	printf("*MESH_FACENORMAL");
				faceflag++;
				k=-1;
				//buf[0]=0;
			}else
			{
			//	puts(buf);
			//	fscanf(f,"\t\t\t*MESH_VERTEXNORMAL %d\t%f %f %f\n",&bb,&temp.x,&temp.z,&temp.y);
				sscanf(buf,"\t\t\t\t*MESH_VERTEXNORMAL %d\t%f %f %f\n",&bb,&temp[0],&temp[2],&temp[1]);
			//	temp[3]=0;
				k++;
				face[faceflag].n[k][0]=temp[0];
				face[faceflag].n[k][1]=temp[1];
				face[faceflag].n[k][2]=temp[2];
			


				face[faceflag].vertexnum[k]=bb;


			}
			}
		}

	}

	
		fclose(g);
}