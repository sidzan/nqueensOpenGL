//******** c program headers **********
#include <iostream>
#include <cstdio>
#include <cstdlib>
//******** OpenGL headers **********
#include <GL/freeglut.h>
#include <GL/gl.h>
//#define N 8 // size of queens size of maxx,maxy
#define dx 30
#define dy 30
using namespace std;

GLfloat x[N+1]={0.0}, y[N+1]={0.0};
GLfloat a0=50, b0=50;
GLint i,j;
int x3=0,y3=0;
int flag =0;  
int board[N][N] = {0};
int colorboard[20][20];
int boardx[10];
int boardy[10];
/* print solution */
void printSolution(int board[N][N])
{
    flag=1;
} 
 
/* check if a queen can be placed on board[row][col]*/
bool isSafe(int board[N][N], int row, int col)
{
    int i, j;
    for (i = 0; i < col; i++)
    {
        if (board[row][i])
            return false;
    }
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j])
            return false;
    }
 
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
    {
        if (board[i][j])
            return false;
    }
 
    return true;
}
 
/*solve N Queen problem */
bool solveNQUtil(int board[N][N], int col)
{
    if (col >= N)
        return true;
    for (int i = 0; i < N; i++)
    {
        if ( isSafe(board, i, col) )
        {
            board[i][col] = 1;
            if (solveNQUtil(board, col + 1) == true)
                return true;
            board[i][col] = 0;
        }
    }
    return false;
}
 
/* solves the N Queen problem using Backtracking.*/
bool solveNQ()
{
    
    if (solveNQUtil(board, 0) == false)
    {   
        flag=0;
        return false;
    }
    printSolution(board);
    return true;
}
 
//rectangular MESH PROGRAM
void myinit()
{
    glClearColor(0.0,0.0,0.0,1.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
    glutPostRedisplay();
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(5);     
    glColor3f(1.0,0.0,0.0);
for(i=0;i<N+1;i++)
    x[i]=a0+i*dx;
for(j=0;j<N+1;j++)
    y[j]=b0+j*dy;
    glColor3f(1.0,0.0,0.0);
for(i=0;i<N;i++)
    for(j=0;j<N;j++)
    {

     /*   for (int i = 0; i < N; i++)
             {
            for (int j = 0; j < N; j++)
                cout<<board[i][j]<<"  ";
                cout<<endl;
            }
    */  
        if(board[i][j]==1)
        {   boardx[x3++]=i;
            boardy[y3++]=j;
            glColor3f(1.0,0.0,0.0);
        }
        else
            {glColor3f(0.0,1.0,0.0);}



        glBegin(GL_LINE_LOOP);
        glVertex2f(x[i],y[j]);
        glVertex2f(x[i],y[j+1]);
        glVertex2f(x[i+1],y[j+1]);
        glVertex2f(x[i+1],y[j]);
        glEnd();
    glFlush();
    }
/*    int m,n;
for(i=0;i<N;i++)
{*/
   for(i=0;i<N;i++)
   {
        glColor3f(1,0,0);
        glBegin(GL_POLYGON);
        glVertex2f(x[boardx[i]],y[boardy[i]]);
        glVertex2f(x[boardx[i]],y[boardy[i]+1]);
        glVertex2f(x[boardx[i]+1],y[boardy[i]+1]);
        glVertex2f(x[boardx[i]+1],y[boardy[i]]);
        glEnd();
    }
//}
glFlush();
}




// Main
int main(int argc,char **argv)
{
    solveNQ();
    if (flag==1)
    {
     glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutInitWindowSize(500.0,500.0);
        glutInitWindowPosition(250.0,250.0);
        
        glutCreateWindow("RECTANGULAR MESH");
                myinit();
        glutDisplayFunc(display);
        //glClearColor(1,1,1,1);
        glutMainLoop();
    }
    else 
		printf("its not going to work\n");
    return 0;
}
