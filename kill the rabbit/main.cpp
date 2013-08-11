
#include <stdio.h>     
#include <GL/glut.h>   
                       
#include "visuals.h"   
#include "stdafx.h"





/////////////// Main Program ///////////////////////////

int main(int argc, char* argv[])
{ 
  // initialize GLUT library state
  glutInit(&argc, argv);
	
  
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
 
  
  // Define the main window size and initial position 

  glutInitWindowSize(1000,800);
  glutInitWindowPosition(50,50);
  
  // Create and label the main window
  glutCreateWindow("kill the rabbit");
  
  

  // Configure various properties of the OpenGL rendering context
  Setup();
  
  // Callbacks for the GL and GLUT events:

  // The rendering function 
  glutDisplayFunc(Render);
  glutReshapeFunc(Resize);
  
  // Time and movment management 
  glutIdleFunc(Idle);
  //keyboard handling
  glutSpecialFunc(keyboard_handle);
  glutKeyboardFunc(keyboard_handle1);
 
  //Enter main event handling loop
  glutMainLoop();
  return 0;


}  

