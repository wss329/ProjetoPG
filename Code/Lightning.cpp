#ifdef __APPLE__
#include <unistd.h>
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif

#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

void EnableLighting(){

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 }; /* bright white */
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_ambient[] = { 0.8, 0.8, 0.8, 1.0 }; /* soft white */

	GLfloat light2_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light2_specular[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat light2_ambient[] = { 1.0, 0.0, 0.0, 1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient); // defining light1 components
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse); 
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient); // defining light2 components
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);

	GLfloat light1_position[] = { 0.0, 1.0, 1.0, 1.0 }; // defining light1 position
	
	GLfloat light2_position[] = { 0.0, 0.0, 0.0, 1.0 }; // definindo posição da light2

	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; //definindo a cor natural do obj, nesse caso azul.
	GLfloat mat_diffuse[] = { 0.0, 0.0, 1.0, 1.0 }; 
	GLfloat mat_ambient[] = { 0.0, 0.0, 1.0, 1.0 }; 
	GLfloat mat_shininess = 2.0;
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}
//falta fazer a translação dos pontos de luz.

