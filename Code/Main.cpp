#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "Model.h"
#include "Light.h"
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

GLfloat wWidth = 1366.0;
GLfloat wHeight = 768.0;

// ---------------Global Vars Start ---------
void loadModels();
void display();
void specialKeys();
void drawRetangle();
void drawGrid();
void selectNext();
void selectLast();
Camera cameraPrincipal = Camera();

vector<Model> objs;
int modelIndex = 0;
double rotate_y = 0;
double rotate_x = 0;

Light L1 = Light();
Light L2 = Light();

// -------------Global Vars End ------------

void display(){
	//  Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//cameraPrincipal.setView();
	//glMatrixMode(GL_PROJECTION);
	//glViewport(wWidth / 20, 0, wWidth - wWidth / 20, wHeight);
	//glLoadIdentity();
	//gluPerspective(45, wWidth / (wHeight), 0.1f, 3000.0f);

	// Reset transformations
	glLoadIdentity();

	// Rotate when user changes rotate_x and rotate_y
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glScalef(0.2, 0.2, 0.2);


	drawGrid();
	for (size_t i = 0; i < objs.size(); i++)
	{
		objs[i].DrawModel();
	}

	// Other Transformations
	//glScalef( 2.0, 2.0, 2.0 );          // Not included


	glFlush();
	glutSwapBuffers();

}

void DisplayLight()
{
	glPushMatrix();
	GLfloat position[] = { L1.pontos.x, L1.pontos.y, L1.pontos.z - 1, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPopMatrix();
	
	glPushMatrix();
	GLfloat position[] = { L2.pontos.x, L2.pontos.y, L2.pontos.z - 1, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glPopMatrix();
}

void LoadModels()
{
	Model m = Model("Resources/Triangles/venus.obj");
	objs.push_back(m);
	// adiciona os modelos no vector
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
	case 49://1
		objs[modelIndex].translate_x -= 0.02;
		break;

	case 50://2
		objs[modelIndex].translate_x += 0.02;
		break;

	case 51://3
		objs[modelIndex].translate_y -= 0.02;
		break;

	case 52://4
		objs[modelIndex].translate_y += 0.02;
		break;

	case 53://5
		objs[modelIndex].translate_z -= 0.02;
		break;

	case 54://6
		objs[modelIndex].translate_z += 0.02;
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