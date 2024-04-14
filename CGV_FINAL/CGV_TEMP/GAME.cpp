#include <stdio.h> 
#include <math.h>
#include <GL/glut.h>
#include <iostream>

#include "GAME.h"
#include "ALL.h"

using namespace std;

void initializeGAME()
{
        finish=-1;

	m.X=850;
	m.Z=-1900;
        m.Y=0;
	m.Speed=0;
        m.uz=0;
        m.ux=-1;

        m.theta=180;
    
        car.SelectModel(1);
        cam.VIEW=2;
	cam.H=20;
        finish=-1;

        T=glutGet(GLUT_ELAPSED_TIME);
	//cam.SetDriveCamera(m.X,m.Y,m.Z,m.ux,m.uz);
	
}




//---------------------------------------------------DRIVE---------------------------------------------------
void displayGAME(void) 
{ 
 
   glClearColor(1,1,1,0);
  
   glClearDepth(1);
   glClear(GL_COLOR_BUFFER_BIT);
   glClear(GL_DEPTH_BUFFER_BIT);

   glEnable(GL_DEPTH_TEST);
  
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glViewport(0,0,800,800);
   gluPerspective(45,1,1,10000);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

  

 
   cam.SetDriveCamera(m.X,m.Y,m.Z,m.ux,m.uz);

   makeRoads();
 
   makeBuildings();
  
   car.DrawCar(m.X,m.Y+2,m.Z,m.theta,wa);
   glutPostRedisplay();
   
 
  if(finish==-1&&count!=100)
   { 
   	
     PrintFlags();

    }

    else if(finish==1&&count==100)
    { cam.fx=m.X;  cam.fy=m.Y; cam.fz=m.Z;   cam.VIEW=9;count++; printScore(); }	

    else if(finish==1)
    {  printScore(); }	


    glFlush(); 


}



void specialGAME(int key,int x,int y)
{
   switch(key)
   {
       case GLUT_KEY_UP:    m.Speed=m.Speed+m.Acc/10; break;
      case GLUT_KEY_DOWN:  m.Speed=m.Speed-m.Acc/10; break; 
      case GLUT_KEY_LEFT:{ m.theta=m.theta-3.5; } break;
      case GLUT_KEY_RIGHT: { m.theta=m.theta+3.5;} break;
     

      case GLUT_KEY_F1:  car.SelectModel(1);  break;
      case GLUT_KEY_F2:  car.SelectModel(2);  break;
      case GLUT_KEY_F3:  car.SelectModel(3);  break;
      case GLUT_KEY_F4:  car.SelectModel(4);  break;

   }

   m.UpdateVector();

   glutPostRedisplay();
}


void keyGAME(unsigned char key,int x,int y)
{
   switch(key)
   {
      case 32:{
                 if(m.Speed>0) 
                {  
                    if(m.Speed<10)
                      m.Speed=0;
                    else
                    m.Speed=m.Speed-10;
                }

                if(m.Speed<0) 
                {  
                    if(m.Speed>-10)
                      m.Speed=0;
                    else
                    m.Speed=m.Speed+10;
                }  
              } break;



     case 'g':
     case 'G': cam.H--;  break;
     case 't':
     case 'T': cam.H++;  break;
    
      case '0':  cam.VIEW=0; break;
      case '1':  cam.VIEW=1; break;
      case '2':  cam.VIEW=2; break;
      case '3':  cam.VIEW=3; break;
      case '4':  cam.VIEW=4; break;
      case '5':  cam.VIEW=5; break;
      case '6':  cam.VIEW=6; break;
      case '7':  cam.VIEW=7; break;
      case '8':  cam.VIEW=8; break;
      case '9': { cam.fx=m.X;  cam.fy=m.Y; cam.fz=m.Z;   cam.VIEW=9; } break;
      
      case 'w':
      case 'W':    m.Speed=m.Speed+m.Acc/10; break;
      case 's':
      case 'S':  m.Speed=m.Speed-m.Acc/10; break; 
      case 'a':
      case 'A':{ m.theta=m.theta-7.5; } break;
      case 'd':
      case 'D': { m.theta=m.theta+7.5;} break;

      case 27: state=0; break;
      
      
   }

   m.UpdateVector();

   glutPostRedisplay();
}




void timeGAME()
{  

  cout<<m.X<<" "<<m.Z<<endl;
   
   omega=m.Speed/4;

   wa=wa+omega;

   m.FreeMotion();

  m.UpdateAcc();

  
   meter();

 
  if(finish==-1)
  {   
  	  
      Stopwatch(T);
      CheckFlag();
  }
   
 
   glutPostRedisplay();
  // glutTimerFunc(t,timeGAME,0);
}


//-------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------


