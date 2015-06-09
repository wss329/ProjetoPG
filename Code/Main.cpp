#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "Model.h"
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

void loadModels();
void display();
void specialKeys();
void drawRetangle();
void drawGrid();
void selectNext();
void selectLast();

vector<Model> objs;
int modelIndex = 0;
double rotate_y = 0;
double rotate_x = 0;

void display(){

	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Rotate when user changes rotate_x and rotate_y
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glScalef(0.2, 0.2, 0.2);
	//drawRetangle();

	for (size_t i = 0; i < objs.size(); i++)
	{
		objs[i].DrawModel();
	}
	
	drawGrid();
	// Other Transformations
	//glScalef( 2.0, 2.0, 2.0 );          // Not included


	glFlush();
	glutSwapBuffers();

}

void LoadModels()
{
	Model m = Model("Resources/Triangles/venus.obj");
	objs.push_back(m);
	m = Model("Resources/Triangles/venus.obj");
	objs.push_back(m);
	// adiciona os modelos no vector
}

void drawRetangle()
{
	glBegin(GL_POLYGON);

	glColor3f(1.0, 0.0, 0.0);     glVertex3f(0.5, -0.5, -0.5);      // P1 is red
	glColor3f(0.0, 1.0, 0.0);     glVertex3f(0.5, 0.5, -0.5);      // P2 is green
	glColor3f(0.0, 0.0, 1.0);     glVertex3f(-0.5, 0.5, -0.5);      // P3 is blue
	glColor3f(1.0, 0.0, 1.0);     glVertex3f(-0.5, -0.5, -0.5);      // P4 is purple

	glEnd();

	// White side - BACK
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	//glColor3f(1.0, 0.0, 1.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	// Green side - LEFT
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	// Blue side - TOP
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
}

void drawGrid() // Draws a grid...
{
	glPushMatrix();
	glColor3f(.3, .3, .3);
	glBegin(GL_LINES);
	for (int i = 0; i <= 10; i++)
	{
		if (i == 0) { glColor3f(.6, .3, .3); }
		else { glColor3f(.25, .25, .25); };
		glVertex3f(i, 0, 0);
		glVertex3f(i, 0, 10);
		if (i == 0) { glColor3f(.3, .3, .6); }
		else { glColor3f(.25, .25, .25); };
		glVertex3f(0, 0, i);
		glVertex3f(10, 0, i);
	};

	glEnd();

	glPopMatrix();
}

void specialKeys(int key, int x, int y) {

	//  Right arrow - increase rotation by 5 degree
	if (key == GLUT_KEY_RIGHT)
		rotate_y += 5;

	//  Left arrow - decrease rotation by 5 degree
	else if (key == GLUT_KEY_LEFT)
		rotate_y -= 5;

	else if (key == GLUT_KEY_UP)
		rotate_x += 5;

	else if (key == GLUT_KEY_DOWN)
		rotate_x -= 5;

	//  Request display update
	glutPostRedisplay();

}

void handleKeypress(unsigned char key, int x, int y)
{
	switch (key){

	case 43://+
		objs[modelIndex].scale += 0.01;
		break;
	case 45://-
		objs[modelIndex].scale -= 0.01;
		break;

	//Arthur RETARDADO LEMBRA QUE e em coordenadas de mundo e n do obj
	case 49://1
		break;
	
	case 50://2
		break;
	
	case 51://3
		break;
	
	case 52://4
		break;
	
	case 53://5
		break;
	
	case 54://6
		break;
	
	case 55://7 gira o objeto selecionado em relação ao eixo X
		objs[modelIndex].rotate_x += 5;
		break;
	
	case 56://8 gira o objeto selecionado em relação ao eixo Y
		objs[modelIndex].rotate_y += 5;
		break;
	
	case 57://9 gira o objeto selecionado em relação ao eixo Z
		objs[modelIndex].rotate_z += 5;
		break;

	case 27: // ESC
		exit(0);
		break;

	case 44://,
		selectLast();
		break;

	case 46://.
		selectNext();
		break;

	case 60://<
		selectLast();
		break;

	case 62://>
		selectNext();
		break;

	}

	glutPostRedisplay();

}

void selectLast()
{
	// implementar a lógica  de primeiro obj ultima fonte de luz etc
	if (modelIndex > 0)
	{
		modelIndex = modelIndex - 1;
		printf("Selected: %s %d \n", objs[modelIndex].nome.c_str(), modelIndex);
	}
//‘,’ ou ‘<’: seleciona o modelo anterior (ao chegar no primeiro modelo, passa para a última fonte de luz)
}

void selectNext()
{
	if (modelIndex < objs.size()-1)
	{
		modelIndex = modelIndex + 1;
		printf("Selected: %s %d \n", objs[modelIndex].nome.c_str(), modelIndex);
	}
//‘.’ ou ‘>’: seleciona o modelo seguinte (ao chegar no último modelo, passa para a primeira fonte de luz)
}

int main(int argc, char* argv[]){

	LoadModels();
	glutInit(&argc, argv);

	//  Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800 , 800);
	// Create window
	glutCreateWindow("Projeto PG");

	//  Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	// Callback functions
	glutDisplayFunc(display);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(handleKeypress);

	//  Pass control to GLUT for events
	glutMainLoop();

	//  Return to OS
	return 0;
}


//#include "Model.h"
//#include "openGL_tutorial.h"
//#include <iostream>
//#include <vector>
//
//
//const int WINDOW_W = 750;
//const int WINDOW_H = 750;
//
//using namespace std;
//
//vector <Model> objetos;
//

//
//
//void display()
//{
//	glMatrixMode(GL_MODELVIEW);
//	
//	glClear(GL_COLOR_BUFFER_BIT);	
//	glLoadIdentity();
//
//	/*for (size_t i = 0; i < objetos.size(); i++)
//	{
//		objetos[i].DrawModel();
//	}*/
//
//	drawGrid();
//
//	glFlush();
//}
//
//
//void reshape(int w, int h)
//{
//	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0.0f, WINDOW_W, WINDOW_H, 0.0f, -5.0, 5.0);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}
//
//int main(int argc, char ** argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//	glutInitWindowPosition(0, 0); // a janela irá iniciar to topo esquerdo
//	glutInitWindowSize(WINDOW_W, WINDOW_H);
//	glutCreateWindow("Projeto PG");
//	//LoadModels();
//	glEnable(GL_DEPTH_TEST);
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	
//	glutKeyboardFunc(handleKeypress);
//	
//	glutMainLoop();
//	
//}