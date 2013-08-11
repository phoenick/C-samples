#include <stdio.h>     
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <time.h>
#include <string>
#include <cstring>
#include <GL/glut.h>   
                       
#include "visuals.h"   


using namespace std;

//////// State Variables ////////

float bunny_v[1458][3];
int bunny_f[2777][3];
double xm , ym , zm;
double brmax;


const double pi=3.14;
const double dt = 0.07;
const double g = 2.0;

double knz_offset = 0.0;
double knx_offset = 0.0;

double a=0.0;

double vpos[3]={ -117.0, 6.0, 0.0};
bool vlimex = false;
double vspeed[3] = {0.0, 0.0, 0.0};
double v0 = 20.0;
const double vr = 4.0;

bool lagex = false;
double lagpos[3]={ -117.0, 6.0, 0.0};
double lagspeed[3] = {0.0, 0.0, 0.0};
double lagv0 = 8.0; 
double laga = 120.0;

double efpos[3];
bool efex = false;

int t;

int score = 0, oldscore = 0, level = 0;



//canon rendering 
void kanoni()
{
	
	glPushMatrix();
    glTranslatef(knx_offset, 0.0, knz_offset);

	glTranslatef(-117.0, 6.0, 0.0);
	//glTranslatef(-117.0, 0.0, 0.0);
    
	//sfera
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.8);
	glutSolidSphere(5.0, 50.0, 50.0);
	glPopMatrix(); 

	//roda1
	glPushMatrix();
	glTranslatef(0.0, 0.0, -5.0);
	glColor3f(0.9, 0.6, 0.0);
	glutSolidTorus( 2.0, 5.0, 8, 24);
	glPopMatrix();
	     


	//roda2
    glPushMatrix();
	glTranslatef(0.0, 0.0, 5.0);
	glColor3f(0.9, 0.6, 0.0);
	glutSolidTorus( 2.0, 5.0, 8, 24);
	glPopMatrix();

	//kanh GL_QUAD_STRIP
    glPushMatrix();
    glRotatef(a, 0.0, 0.0 , 1.0 );
	glColor3f(1.0, 0.0, 0.0);
	glRotatef(-90.0 , 0.0 , 0.0 , 1.0);
	glBegin(GL_QUAD_STRIP);
	for(int i=0 ; i<32 ; i++) {
		glNormal3f(cos(i*2*pi/32),0.0,sin(i*2*pi/32));
		glVertex3f(5*cos(i*2*pi/32) , 0.0 , 5*sin(i*2*pi/32));
	    glVertex3f(5*cos(i*2*pi/32) , 20.0 , 5*sin(i*2*pi/32));
	}
    glNormal3f(cos(0*2*pi/32),0.0,sin(0*2*pi/32));
    glVertex3f(5*cos(0*2*pi/32) , 0.0 , 5*sin(0*2*pi/32));
	glVertex3f(5*cos(0*2*pi/32) , 20.0 , 5*sin(0*2*pi/32));

	glEnd();
    glPopMatrix(); 

    glPopMatrix(); 




	   
}

//ground rendering
void edafos()
{	//glTranslatef(0.0, 0.0, -100.0);
	glPushMatrix();
	
	//glTranslatef(-40.0, 0.0, 0.0);
    glNormal3f(0.0 , 1.0 , 0.0);
	glBegin(GL_QUAD_STRIP);
	//glColor3f(0.1, 0.7, 0.2);
	const double step = 12.5;
	for(int i=-1  ; i<22 ; i++) {
	  if(i % 2 == 0)
         glColor3f(0.0, 0.5, 0.0);
	  else
         glColor3f(0.0, 0.3, 0.0);
      glVertex3f(-125.0, 0.0, 125.0 - i*step);
	  glVertex3f(125.0, 0.0, 125.0 - i*step);
	}
	glEnd();
	glPopMatrix(); 	 	
}

//ui stats rendering
void pinakas_endei3eon() {
	glPushMatrix();
	glTranslatef(0.0, 0.0, -137.5);
	glRotatef(30.0, -1.0, 0.0, 0.0);
	glColor3f(0.45, 0.45, 0.0);
	glBegin(GL_POLYGON);
    glNormal3f(0.0 , 0.0 , 1.0);
	glVertex3f(-125.0 , 0.0 , 0);
    glVertex3f(-125.0 , 60.0 , 0);
    glVertex3f(125.0 , 60.0 , 0);
    glVertex3f(125.0 , 0.0 , 0);
	glEnd();
	glPopMatrix();

	unsigned char buf[50];
    glPushMatrix();	
	glTranslatef(-100.0, 40.0 , -137.5);
	glRotatef(30.0, -1.0, 0.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	glLineWidth(3.0);
	sprintf((char*)buf,"Angle: %d", (int)a);
    glPushMatrix();
	glColor3f(0.8, 0.0, 0.0);
	for (int i=0;i<7;i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,buf[i]);
    glPopMatrix();
	glPushMatrix();
	glTranslatef(400.0, 0.0 , 0.0);
	glColor3f(1.0, 1.0, 1.0);
	for (int i=7;buf[i] != '\0';i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,buf[i]);
    glPopMatrix();
	glPopMatrix(); 

	
    glPushMatrix();	
	glTranslatef(-100.0, 20.0 , -137.5);
	glRotatef(30.0, -1.0, 0.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	glLineWidth(3.0);
	sprintf((char*)buf,"Power: %d", (int)v0);
    glPushMatrix();
	glColor3f(0.8, 0.0, 0.0);
	for (int i=0;i<7;i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,buf[i]);
    glPopMatrix();
	glPushMatrix();
	glTranslatef(400.0, 0.0 , 0.0);
	glColor3f(1.0, 1.0, 1.0);
	for (int i=7;buf[i] != '\0';i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,buf[i]);
    glPopMatrix();
	glPopMatrix(); 

	
    glPushMatrix();	
	glTranslatef(30.0, 40.0 , -137.5);
	glRotatef(30.0, -1.0, 0.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	glLineWidth(3.0);
	sprintf((char*)buf,"Score: %d", score);
    glPushMatrix();
	glColor3f(0.8, 0.0, 0.0);
	for (int i=0;i<7;i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,buf[i]);
    glPopMatrix();
	glPushMatrix();
	glTranslatef(400.0, 0.0 , 0.0);
	glColor3f(1.0, 1.0, 1.0);
	for (int i=7;buf[i] != '\0';i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,buf[i]);
    glPopMatrix();
	glPopMatrix(); 

	
    glPushMatrix();	
	glTranslatef(30.0, 20.0 , -137.5);
	glRotatef(30.0, -1.0, 0.0, 0.0);
	glScalef(0.1, 0.1, 0.1);
	glLineWidth(3.0);
	sprintf((char*)buf,"Level: %d", level);
    glPushMatrix();
	glColor3f(0.8, 0.0, 0.0);
	for (int i=0;i<7;i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,buf[i]);
    glPopMatrix();
	glPushMatrix();
	glTranslatef(400.0, 0.0 , 0.0);
	glColor3f(1.0, 1.0, 1.0);
	for (int i=7;buf[i] != '\0';i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,buf[i]);
    glPopMatrix();
	glPopMatrix(); 


}

//3d model loading and rendering
void lagoudaki()
{   glPushMatrix();
	//glTranslatef(0.0, 7.5, 0.0);
	glTranslatef(lagpos[0], lagpos[1], lagpos[2]);
	glScalef(15.0 , 15.0 , 15.0);
    glScalef((float)1/brmax , (float)1/brmax , (float)1/brmax);
	glTranslatef(-xm, -ym, -zm);
    //glScalef(1.0 , 5 , 5);
	
    glRotatef(90.0, 0.0, 1.0, 0.0);

    glBegin(GL_TRIANGLES);
	glColor3f(0.7,0.7, 0.7);
    for(int i=0 ; i<2777 ; i++){
		double nx , ny , nz , v1[3] , v2[3];
		int p1 = bunny_f[i][0]-1;
        int p2 = bunny_f[i][1]-1;
        int p3 = bunny_f[i][2]-1;
    	//glColor3f((float)i/(float)1000,0.0, 0.2);
		
		v1[0] = bunny_v[p3][0]-bunny_v[p1][0];
        v1[1] = bunny_v[p3][1]-bunny_v[p1][1];
        v1[2] = bunny_v[p3][2]-bunny_v[p1][2];
		v2[0] = bunny_v[p2][0]-bunny_v[p1][0];
		v2[1] = bunny_v[p2][1]-bunny_v[p1][1];
		v2[2] = bunny_v[p2][2]-bunny_v[p1][2];
		nx = v1[1] * v2[2] - v1[2] * v2[1];
		ny = v1[2] * v2[0] - v1[0] * v2[2];
        nz = v1[0] * v2[1] - v1[1] * v2[0];
		double m = sqrt(nx*nx + ny*ny + nz*nz);
		nx /= m;
		ny /= m;
		nz /= m;
        glNormal3f(-nx , -ny , -nz);
        glVertex3f(bunny_v[p1][0] , bunny_v[p1][1], bunny_v[p1][2]);
        glVertex3f(bunny_v[p2][0] , bunny_v[p2][1], bunny_v[p2][2]);
        glVertex3f(bunny_v[p3][0] , bunny_v[p3][1], bunny_v[p3][2]);
       
    }
     glEnd();
    glPopMatrix();
}

//projectile rendering
void vlima() {
    glPushMatrix();
	glTranslatef(vpos[0] , vpos[1] , vpos[2]);
    glColor3f(0.9, 0.7, 0.0);
    glutSolidSphere(vr, 32.0, 32.0);
    glPopMatrix();
}

//explosion rendering
void efe_sygroushs() {
	glPushMatrix();
	glTranslatef(efpos[0] , efpos[1] , efpos[2]);

	glPushMatrix();
	glScalef(2.3, 2.3, 2.3);
	glRotatef(30.0, 0.0, 0.0, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	
	glColor3f(0.9, 0.9, 0.0);
    glBegin(GL_TRIANGLES);
	glNormal3f(0.0, 1.0, 0.0);
    for(int i=0 ; i<6 ; i+=2) 
      glVertex3f(8*cos(i*pi/3) , 0.0 , 8*sin(i*pi/3));
    for(int i=1 ; i<6 ; i+=2) 
	  glVertex3f(8*cos(i*pi/3) , 0.0 , 8*sin(i*pi/3));
	glEnd();
	glPopMatrix();

	glPushMatrix();	
	glTranslatef(-9.0, -4.0 , 0.2);
	glScalef(0.1, 0.1, 0.1);
	glColor3f(0.9, 0.0, 0.0);
	glLineWidth(3.0);
	unsigned char str[] = "Hit!";
	for (int i=0;str[i] != '\0';i++)
	  glutStrokeCharacter(GLUT_STROKE_ROMAN,str[i]);
	glPopMatrix();

	glPopMatrix();
}

void Render()
{    
  
  glClear(GL_COLOR_BUFFER_BIT);
  glClear(GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  

  gluLookAt(0.0, 240.0, 280.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
 

  edafos();
  pinakas_endei3eon();
  if(efex == true)
    efe_sygroushs();
  if(lagex == true)
    lagoudaki();
  kanoni();
  if(vlimex == true)
	vlima();
	
  glutSwapBuffers();                  

}

//-----------------------------------------------------------


void Resize(int w, int h)
{ 
  // define the visible area of the window
  if (h==0) h=1;
  glViewport(0,0,w,h); 

  // Setup viewing volume

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
 
  gluPerspective(45.0, (float)w/(float)h, 1.0, 500.0);
 
}

//Time, movement and events management
void Idle()
{   if(efex == true) 
	   if((clock()-t)/(float)CLOCKS_PER_SEC > 3)
		   efex = false;
	if(vlimex == true) {
	  if(lagex == true) {
	    double d;
		d = sqrt((lagpos[0]-vpos[0])*(lagpos[0]-vpos[0]) + (lagpos[1]-vpos[1])*(lagpos[1]-vpos[1]) + (lagpos[2]-vpos[2])*(lagpos[2]-vpos[2]));
		
		if(d < 4+7.0) {
			score += 25;
			if(score - oldscore >= 100){
				oldscore = score;
				level++;
				lagv0 += 2.0;
			}
			vlimex = false;
			lagex = false;
			efex = true;
			efpos[0] = vpos[0];
			efpos[1] = vpos[1];
			efpos[2] = vpos[2];
			t = clock();
			glutPostRedisplay();
			return;
		}
	  }
		if(vpos[1] > vr) {
           vpos[0] += vspeed[0] * dt;
		   vpos[1] += vspeed[1]*dt - 1/2*g*dt*dt;
		   vspeed[1] -= g*dt;
		}
		else
			vlimex = false;
	}

    if(lagex == true) {
	  if(lagpos[0] > -125) {
		if(lagpos[1] > 7.5) {
		  
           lagpos[0] += lagspeed[0] * dt;
		   lagpos[1] += lagspeed[1]*dt - 1/2*g*dt*dt;
		   lagspeed[1] -= g*dt;
		}
		else {
		   lagspeed[1] *= -1;
		   lagpos[0] += lagspeed[0] * dt;
		   lagpos[1] += lagspeed[1]*dt - 1/2*g*dt*dt;
		   lagspeed[1] -= g*dt;
		}
	  }
	  else
		  lagex = false;
	}

	
	glutPostRedisplay();


}

void keyboard_handle(int key , int x , int y) {
	switch(key) {
		case GLUT_KEY_LEFT :
			 if(knx_offset !=0.0)
			    knx_offset += -12.5;
		    break;
        case GLUT_KEY_RIGHT :
           if(knx_offset != 237.5)
				knx_offset += 12.5;
			break;
        case GLUT_KEY_DOWN :
			if(knz_offset != 125.0)
				knz_offset += 12.5;
			break;
        case GLUT_KEY_UP :
			 if(knz_offset != -125.0)
			    knz_offset += -12.5;
		    break;
            
	}
	glutPostRedisplay();
}

void keyboard_handle1(unsigned char key , int x , int y) {
	switch(key) {
		case 'f':
			if(vlimex != true) {
                vlimex = true;
				vpos[0] = -117.0 + knx_offset;
				vpos[1] = 6.0;
                vpos[2] = knz_offset;
				vspeed[0] = v0*cos(a*pi/(float)180);
				vspeed[1] = v0*sin(a*pi/(float)180);
		    }
			break;
        case 'r':
			if(lagex != true) {
				srand(time(NULL));
			    lagex = true;
				lagpos[0] = 150.0;
				lagpos[1] = 8.0;
                lagpos[2] = 125.0 - (rand()%20)*12.5;
				//lagpos[2] = 125.0;
				lagspeed[0] = lagv0*cos(laga*pi/(float)180);
				lagspeed[1] = lagv0*sin(laga*pi/(float)180);
				
			}
		    break;
		case 'a':
			if(v0 < 40.0 )
				v0 += 5.0;
			break;
		case 'z':
			if(v0 > 15.0)
				v0 -= 5.0;
			break;
		case 's':
			if(a != 180.0)
			    a += 10.0;
			break;
		case 'x':
			 if(a != 0.0)
			    a += -10.0;
			break;
	}
	glutPostRedisplay();
}



//-----------------------------------------------------------

void Setup()
{
	/* Load the Bunny */
	ifstream bfile("bunny2.obj"); 
    string line;
    
	
	
	for(int i=0 ; i<4 ; i++)
		getline(bfile , line);
	
	for(int i=0 ; i<1458 ; i++){
		getline(bfile , line);
	    sscanf(line.c_str() , "v %f %f %f " , &bunny_v[i][0] , &bunny_v[i][1] , &bunny_v[i][2]);
	}
	
	
	
	
	for(int i=0 ; i<5 ; i++)
		getline(bfile , line);
		
   for(int i=0 ; i<2777 ; i++){
	   getline(bfile , line);
	   sscanf(line.c_str() , "f %d %d %d " , &bunny_f[i][0] , &bunny_f[i][1] , &bunny_f[i][2]);
   }
  
	
   
   double tx=0 , ty=0 , tz=0;
   
   for(int i=0 ; i<1458 ; i++) {
        tx += bunny_v[i][0];
        ty += bunny_v[i][1];
	    tz += bunny_v[i][2];
	}
	xm = tx/1458;
	ym = ty/1458;
	zm = tz/1458;
	
	double tmp;
    for(int i=0 ; i<1458 ; i++) {
        tmp = sqrt((bunny_v[i][0]-xm)*(bunny_v[i][0]-xm)+(bunny_v[i][1]-ym)*(bunny_v[i][1]-ym)+(bunny_v[i][2]-zm)*(bunny_v[i][2]-zm));
        if(tmp > brmax)
            brmax = tmp;
      
	}
  

   glShadeModel( GL_SMOOTH );
   

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);
   glDepthFunc( GL_LEQUAL );      
   glClearDepth(1.0); 		      


   //Set up light source
   GLfloat ambientLight[] = { 0.2, 0.2, 0.2, 1.0 };
   GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
   GLfloat lightPos[] = { -20.0, 20.0, 150.0, 1.0 };

   glLightfv( GL_LIGHT0, GL_AMBIENT, ambientLight );
   glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLight );
   glLightfv( GL_LIGHT0, GL_POSITION,lightPos );

 
	// polygon rendering mode and material properties
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
   
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
   
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0);



	// Black background
	glClearColor(0.0f,0.4f,0.7f,1.0f);

}






