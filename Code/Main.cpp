#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "Model.h"
#include "Light.h"
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h>

// ---------------Global Vars Start ---------
void DisplayLights();
void loadModels();
void display();
void specialKeys();
void drawRetangle();
void drawGrid();
void selectNext();
void selectLast();
void translateModel(int selector, double deslocamento);
Camera cameraPrincipal = Camera();
vector<Model> objs;
int modelIndex = 0;
double tempRotate_y = 0;
double tempRotate_x = 0;
const double translateQtd = 0.02;
Light L1 = Light();
Light L2 = Light();
int lightIndex = 0;
bool lightSelected = 0;
double mousepos_x = 0;
double mousepos_y = 0;
bool click = false;
bool mouse_right = false;
GLfloat wWidth = 1366.0;
GLfloat wHeight = 768.0;

void idle(void);
int frameCount = 0;
float fps = 0;
int currentTime = 0, previousTime = 0;
void calculateFPS();
void drawFPS();
void printw(float x, float y, float z, char* format, ...);
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;


// -------------Global Vars End ------------

void display(){

	//  Clear screen and Z-buffer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//--------------------------Camera Setup --------------------------------
	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, wWidth / 2, wHeight);
	glLoadIdentity();
	gluPerspective(45, wWidth / (wHeight * 2), 0.1f, 3000.0f);
	cameraPrincipal.setView();
	//-----------------------------------------------------------------------
	
	DisplayLights();
	for (size_t i = 0; i < objs.size(); i++)
	{
		objs[i].DrawModel();
	}
	//drawGrid();
	drawFPS();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void drawFPS()
{
	//  Load the identity matrix so that FPS string being drawn
	//  won't get animates
	glLoadIdentity();

	//  Print the FPS to the window
	printw(-0.9, -0.9, 0, "FPS: %4.2f", fps);
}

void DisplayLights()
{
	glPushMatrix();
	GLfloat position[] = { L1.pontos.x, L1.pontos.y, L1.pontos.z - 1, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPopMatrix();
	
	glPushMatrix();
	GLfloat position2[] = { L2.pontos.x+ 5, L2.pontos.y, L2.pontos.z - 1, 1.0 };
	GLfloat color[] = { 0.89, 0, 0.87 };
	glLightfv(GL_LIGHT1, GL_POSITION, position2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, color);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glPopMatrix();
}

void LoadModels()
{
	//m = Model("Resources/Triangles/venus.obj");
	//objs.push_back(m);
	Model m = Model("Resources/PolygonsWithNormals/camel.obj");
	objs.push_back(m);
}

void printw(float x, float y, float z, char* format, ...)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	va_list args;	//  Variable argument list
	int len;		//	String length
	int i;			//  Iterator
	char * text;	//	Text

	//  Initialize a variable argument list
	va_start(args, format);

	//  Return the number of characters in the string referenced the list of arguments.
	//  _vscprintf doesn't count terminating '\0' (that's why +1)
	len = _vscprintf(format, args) + 1;

	//  Allocate memory for a string of the specified size
	text = (char *)malloc(len * sizeof(char));

	//  Write formatted output using a pointer to the list of arguments
	vsprintf_s(text, len, format, args);

	//  End using variable argument list 
	va_end(args);
	//  Specify the raster position for pixel operations.,
	glRasterPos3f(x, y, z);
	//  Draw the characters one by one
	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);
	//  Free the allocated memory for the string
	free(text);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}	


void calculateFPS()
{
	//  Increase frame count
	frameCount++;

	//  Get the number of milliseconds since glutInit called 
	//  (or first call to glutGet(GLUT ELAPSED TIME)).
	currentTime = glutGet(GLUT_ELAPSED_TIME);

	//  Calculate time passed
	int timeInterval = currentTime - previousTime;

	if (timeInterval > 1000)
	{
		//  calculate the number of frames per second
		fps = frameCount / (timeInterval / 1000.0f);

		//  Set time
		previousTime = currentTime;

		//  Reset frame count
		frameCount = 0;
	}
}


void idle(void)
{
	//  Calculate FPS
	calculateFPS();

	//  Call display function (draw the current frame)
	glutPostRedisplay();
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

void handleKeypress(unsigned char key, int x, int y)
{
	switch (key){
		//translateQtd
	case 43://+
		if (!lightSelected)
			objs[modelIndex].scale += 0.01;
		break;
	case 61://=
		if (!lightSelected)
			objs[modelIndex].scale += 0.01;
		break;
	case 45://-
		if (!lightSelected)
			objs[modelIndex].scale -= 0.01;
		break;
	case 95://_
		if (!lightSelected)
			objs[modelIndex].scale -= 0.01;
		break;
	case 49://1
		translateModel(0, -translateQtd);
		break;

	case 50://2
		translateModel(0, +translateQtd);
		break;

	case 51://3
		translateModel(1, -translateQtd);
		break;

	case 52://4
		translateModel(1, +translateQtd);
		break;

	case 53://5
		translateModel(2, -translateQtd);
		break;

	case 54://6
		translateModel(2, +translateQtd);
		break;

	case 55://7 gira o objeto selecionado em relação ao eixo X
		if (!lightSelected)
			objs[modelIndex].rotate_x += 5;
		break;
	case 56://8 gira o objeto selecionado em relação ao eixo Y
		if (!lightSelected)
			objs[modelIndex].rotate_y += 5;
		break;

	case 57://9 gira o objeto selecionado em relação ao eixo Z
		if (!lightSelected)
			objs[modelIndex].rotate_z += 5;
		break;

	case 27: // ESC
		exit(0);
		break;

	case 119: //w
		cameraPrincipal.translateGlob(0, 0, 0.01);
		break;

	case 115: //s
		cameraPrincipal.translateGlob(0, 0, -0.01);
		break;

	case 97: //a
		cameraPrincipal.translateGlob(-0.01,0, 0);
		break;

	case 100: //d
		cameraPrincipal.translateGlob(0.01, 0, 0);
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

void translateModel(int selector, double deslocamento)
{
	//select: x = 0; y = 1 ; z=2;
	const double translateLightBoost = 1;
	if (selector == 0)
	{
		if (!lightSelected)
		{
			objs[modelIndex].translate_x += deslocamento;
		}
		else{
			if (lightIndex == 0)
			{
				L1.translate(deslocamento +translateLightBoost, 0, 0);
			}
			else{
				L2.translate(deslocamento +translateLightBoost, 0, 0);
			}
		}

	}
	else if (selector == 1){
		if (!lightSelected)
		{
			objs[modelIndex].translate_y += deslocamento;
		}
		else{
			if (lightIndex == 0)
			{
				L1.translate(0, deslocamento + translateLightBoost, 0);
			}
			else{
				L2.translate(0, deslocamento + translateLightBoost, 0);
			}
		}
	}
	else if(selector == 2){
		if (!lightSelected)
		{
			objs[modelIndex].translate_z += deslocamento;
		}
		else{
			if (lightIndex == 0)
			{
				L1.translate(0, 0, deslocamento + translateLightBoost);
			}
			else{
				L2.translate(0, 0, deslocamento + translateLightBoost);
			}
		}
	}
}

void selectLast()
{
	if (modelIndex > 0 && !lightSelected)
	{
		//caso 0
		modelIndex = modelIndex - 1;
		printf("Selected: %s %d \n", objs[modelIndex].nome.c_str(), modelIndex);
	}
	else
	{
		if (!lightSelected)
		{
			//caso 1
			lightSelected = 1;
			lightIndex = 1;
			printf("Selected: %s %d \n", "Light ", lightIndex);
		}
		else
		{
			if (lightIndex == 1)
			{
				//caso 2
				lightIndex = 0;
				printf("Selected: %s %d \n", "Light ", lightIndex);
			}
			else
			{
				//caso 3
				lightSelected = 0;
				modelIndex = objs.size() - 1;
				printf("Selected: %s %d \n", objs[modelIndex].nome.c_str(), modelIndex);
			}
		}
	}
}

void selectNext()
{
	if (modelIndex < objs.size()-1 && !lightSelected)
	{
		modelIndex = modelIndex + 1;
		printf("Selected: %s %d \n", objs[modelIndex].nome.c_str(), modelIndex);
	}
	else
	{
		if (!lightSelected)
		{
			//caso 4
			lightSelected = 1;
			lightIndex = 0;
			printf("Selected: %s %d \n", "Light ", lightIndex);
		}
		else
		{
			if (lightIndex == 0)
			{
				//caso 5
				lightIndex = 1;
				printf("Selected: %s %d \n", "Light ", lightIndex);
			}
			else
			{
				//caso 6
				lightSelected = 0;
				modelIndex = 0;
				printf("Selected: %s %d \n", objs[modelIndex].nome.c_str(), modelIndex);
			}
		}
	}
}

void mouseClickFunction(int btn, int state, int x, int y){
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		if (!click){
			click = true;
			mousepos_x = x;
			mousepos_y = y;
		}
	}
	else if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP){
		if (click){
			click = false;
		}
	}
}

void mouseMotion(int x, int y){
	if (!mouse_right){
		if (click){
			cameraPrincipal.rotateGlob((x - mousepos_x)*0.2, 0, 1, 0);
			cameraPrincipal.rotateGlob((y - mousepos_y)*0.2, 1, 0, 0);
		}
		mousepos_x = x;
		mousepos_y = y;
	}
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
	glutIdleFunc(idle);
	glutKeyboardFunc(handleKeypress);

	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseClickFunction);

	//  Pass control to GLUT for events
	glutMainLoop();

	//  Return to OS
	return 0;
}
