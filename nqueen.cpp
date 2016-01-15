#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<GL/glut.h>
int n;
int c[10]={0.0},d[10]={0.0};
int dx=10,dy=10;
int a[10]={0,0,0,0,0,0,0,0,0,0};
int b[10]={0,0,0,0,0,0,0,0,0,0};
GLfloat x[10]={0,0,0,0,0,0,0,0,0,0};
GLfloat y[10]={0,0,0,0,0,0,0,0,0,0};
int r=0;
int t[10]={0,0,0,0,0,0,0,0,0,0};
int counter;
int currentstate=0;
int sx=5, sy=5, loopcount=1;
void display();

void nqueen();

//A Function To Check If The Queen Can Be Placed At A Given Condition

int canplace(int r)
{
	unsigned int i;
	for(i=0;i<r;i++)
	{
		if((x[i]==x[r])||(fabs(y[i]-y[r])==fabs(x[i]-x[r])))
		{
			printf("successful");
			return 0;
		}
	}
	printf("unsuccessful\n");
	return 1;
}

//A Function For The Start Page Movements
void move_start()
{
	glPushMatrix();				//For Red Sphere
	glTranslatef(sx,sy,0.0);
	glColor3f(1.0,0.0,0.0);
	glutSolidSphere(1.5,300,10);
	//glutSolidCube(2.0);
	glPopMatrix();

	glPushMatrix();				//For Green Sphere
	glTranslatef((n*10)-sx,(n*10)-sy,0.0);
	glColor3f(0.0,1.0,1.0);
	glutSolidSphere(1.5,300,10);
//	glutSolidCube(2.0);
	glPopMatrix();

	if(loopcount==1)
	{
		if(sx!=((n*10)-5))
			sx++;
		else if(sy!=((n*10)-5))
			sy++;
		else if(sx==((n*10)-5) && sy==((n*10)-5))
			loopcount=2;
	}
	else
	{
		if(sx!=5)
			sx--;
		else if(sy!=5)
			sy--;
		else if(sx==5 && sy==5)
			loopcount=1;
	}
}

//The Idle Function Definition

void myidle()
{
	if(currentstate==0)
		glutPostRedisplay(); 
	Sleep(70);
}

//A Mouse Function That Defines The Procedure To Be Followed When Mouse Interrupt Occurs
void mymouse(int button, int state, int x, int y)
{
	if((button==GLUT_LEFT_BUTTON || button==GLUT_RIGHT_BUTTON )&& state==GLUT_DOWN)
		currentstate=1; glutPostRedisplay();
}

void keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
	case 27:exit(0);
		break;
	default:glutDisplayFunc(display);
	}
}
//A Function To Draw The Checker Board

void draw_checker()
{
	unsigned int i,j;
	glClear(GL_COLOR_BUFFER_BIT);
	for(i=0;i<n+2;i++)
		c[i]=c[0]+i*dx;
	for(i=0;i<n+2;i++)
		d[i]=d[0]+i*dy;
	for(i=0;i<n;i+=2)
	{
		for(j=0;j<n;j+=2)
		{
		   //glColor3f(0.0,0.0,0.0);
		glColor3f(0.0,0.0,0.7);   glBegin(GL_POLYGON);
		   glVertex3i(c[i],d[j],-10);
		   glVertex3i(c[i],d[j+1],-10);
		   glColor3f(0.2,0.2,0.2);
		   glVertex3i(c[i+1],d[j+1],-10);
		   glVertex3i(c[i+1],d[j],-10);
		   glEnd();
		}
	}
	for(i=1;i<n;i+=2)
	{
		for(j=1;j<n;j+=2)
		{
		   glColor3f(0.0,0.0,0.0);
		   glBegin(GL_POLYGON);
		   glVertex3i(c[i],d[j],-10);
		   glVertex3i(c[i],d[j+1],-10);
		   glColor3f(0.2,0.2,0.2);
		   glVertex3i(c[i+1],d[j+1],-10);
		   glVertex3i(c[i+1],d[j],-10);
		   glEnd();
		}
	}
}

//A Function To Draw Queen

void move_queen()
{
	unsigned int i;
	for(i=0;i<n;i++)
	{		
		if(a[i]==1 && b[i]==0)
		{
			glPushMatrix();
			glTranslatef(x[i],y[i],0.0);
			glColor3f(1.0,0.0,0.0);
			glutSolidSphere(1.5,300,10);
			//glutSolidCube(2.0);
			glPopMatrix();						
		}
	}
	for(i=0;i<n;i++)
	{
		if(a[i]==1 && b[i]==1)
		{
			glPushMatrix();
			glTranslatef(x[i],y[i],0.0);
			glColor3f(0.0,1.0,1.0);
			glutSolidSphere(1.5,300,10);
			//glutSolidCube(2.0);
			glPopMatrix();
		}
	}
}

//The Display Function

void display()
{
	unsigned int i;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,5.0,0.0,0.0,-10.0,0.0,1.0,-1.0);
		
	if(currentstate==0)
	{
		//glClearColor(0.75,0.75,0.75,1.0); 
		glClearColor(1,1,1,1);
	//	char line1[]="PRESENTING...";
		char line2[]=" N-Queens Backtracking";
		char line3[]="The Solution for N-queens with";
		glColor3f(0.0,0.0,0.7);
		/*glRasterPos2i((n*10)/4-2,(n*5)+10);
		for(i=0;i<strlen(line1);i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,line1[i]);
		}*/
		glRasterPos2i((n*10)/4-2,(n*5)+5);
		for(i=0;i<strlen(line2);i++)
		{
				
			//glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,line2[i]);

glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,line2[i]);
		}
		glRasterPos2i((n*10)/4-2,(n*5));
		for(i=0;i<strlen(line3);i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,line3[i]);
		}

		if(n==4)
		{
			char line4[]="N=4";
			glColor3f(0.0,0.0,0.7);
			glRasterPos2i((n*10)/4-2,(n*5)-5);
			for(i=0;i<strlen(line4);i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,line4[i]);
			}
		}

		if(n==5)
		{
			char line4[]="N=5";
			glColor3f(0.0,0.0,0.7);
			glRasterPos2i((n*10)/4-2,(n*5)-5);
			for(i=0;i<strlen(line4);i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,line4[i]);
			}			
		}
		
		if(n==6)
		{
			char line4[]="N=6";
			glColor3f(0.0,0.0,0.7);
			glRasterPos2i((n*10)/4-2,(n*5)-5);
			for(i=0;i<strlen(line4);i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,line4[i]);
			}			
		}
		
		if(n==7)
		{
			char line4[]="N=7";
			glColor3f(0.0,0.0,0.7);
			glRasterPos2i((n*10)/4-2,(n*5)-5);
			for(i=0;i<strlen(line4);i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,line4[i]);
			}
			
		}

		if(n==8)
		{
			
			char line4[]="N=8";
			glColor3f(0.0,0.0,0.7);
			glRasterPos2i((n*10)/4-2,(n*5)-5);
			for(i=0;i<strlen(line4);i++)
			{
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,line4[i]);
			}
			
		}
		char line5[]="Click To Proceed..";
		glColor3f(0.0,0.0,0.7);
		glRasterPos2i((n*10)/4-2,(n*5)-10);
		for(i=0;i < strlen(line5);i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,line5[i]);
		}
		glutKeyboardFunc(keyboard);
	//	move_start();
		glutSwapBuffers();
		glFlush();
	}
	
	else
	{
			while(r>=0 && r<n)
			{
				a[r]=1;
				y[r]=(n*10-5)-10*r;
				if(t[r]==0)		//To Place The Queen In The First Position
				{
					for(counter=0;counter<5;counter++)
					{
						x[r]=x[r]+1;
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
						draw_checker();
						move_queen();
						glutSwapBuffers();
						glFlush();
						Sleep(80);					  					
					}
					Sleep(500);
					t[r]=1;
				}
				else
				{
					for(counter=0;counter<10;counter++)
					{
						x[r]=x[r]+1;
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
						draw_checker();
						move_queen();
						glutSwapBuffers();
						glFlush();
						Sleep(80);					  					
					}
					Sleep(500);						
				}
								
				while(x[r]<n*10 && !canplace(r)) //Check If Can Be Placed, Else Move To Next Position
				{
					for(counter=0;counter<10;counter++)
					{
						x[r]=x[r]+1;
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
						draw_checker();
						move_queen();
						glutSwapBuffers();
						glFlush();
						Sleep(80);						
					}
					Sleep(500);
					
				
				}
				if(x[r]<n*10)
				{
					if(r==n)  //Last Row Queen Is Placed
					{
						
						b[r]=1;
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
						draw_checker();
						move_queen();
						glutSwapBuffers();
						glFlush();
						Sleep(80);
						r++;
						continue;						
					}
					else
					{
						b[r]=1;    //Place The Queen At The Current Location, Move To Next Queen
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
						draw_checker();
                        /*if(n==4)
						{
							glBegin(GL_POLYGON);
							glColor3f(1.0,0.0,0.0);
							glVertex3i(c[10],d[30],0);
		                    glVertex3i(c[20],d[30],0);
                            glVertex3i(c[10],d[40],0);
					     	glVertex3i(c[20],d[40],0);
						     glEnd();
						}*/
						move_queen();
						glutSwapBuffers();
						glFlush();
						Sleep(80);
						r++;
					}
					Sleep(500);
				}
				else
				{
					a[r]=0; b[r]=0; //Queen Cant Be Placed In Any Of The Locations In the Row
					x[r]=0; t[r]=0;
					r--;			//Move To The Previous Row
					a[r]=1;
					b[r]=0;			
				}
				Sleep(500);
			}	
			Sleep(2500);
			glutSwapBuffers();
			glutKeyboardFunc(keyboard);
			glFlush();
	}
}


void myinit()
{
	glClearColor(0.8,0.8,0.8,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,n*10,0,n*10,0,n*10);
	glMatrixMode(GL_MODELVIEW);
	GLfloat mat_diffuse[]={0.0,1.0,1.0,1.0};
	GLfloat light_position[]={n*5,n*5,1.0,1.0};
	GLfloat mat_specular[]={0.0,1.0,1.0,1.0};
	GLfloat mat_shininess[]={25.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,mat_shininess);
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
}

void main(int argc,char **argv)
{
	glutInit(&argc,argv);
	printf("\n\n\t\tEnter The Value For Number Of Queens: ");
	scanf("%d",&n);	
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutCreateWindow("N Queens");
	myinit();
	glutDisplayFunc(display);
	glutIdleFunc(myidle);
	glutMouseFunc(mymouse);
	glutKeyboardFunc(keyboard);
    glutMainLoop();
}
