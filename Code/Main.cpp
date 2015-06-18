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
	glViewport(0, 0, wWidth, wHeight);
	glLoadIdentity();
	gluPerspective(45, wWidth / (wHeight * 2), 0.1f, 3000.0f);
	cameraPrincipal.setView();
	//-----------------------------------------------------------------------

	DisplayLights();
	for (size_t i = 0; i < objs.size(); i++)
	{
		objs[i].DrawModel();
	}
	drawGrid();
	drawFPS();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void drawFPS()
{
	glLoadIdentity();

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
	GLfloat position2[] = { L2.pontos.x + 5, L2.pontos.y, L2.pontos.z - 1, 1.0 };
	GLfloat color[] = { 0.05, 0.98, 0.56 };
	glLightfv(GL_LIGHT1, GL_POSITION, position2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, color);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glPopMatrix();
}

void LoadModels()
{
	Model m = Model("Resources/Triangles/venus.obj");
	objs.push_back(m);

	m = Model("Resources/PolygonsWithNormals/camel.obj");
	objs.push_back(m);

	m = Model("Resources/PolygonsWithNormals/camera.obj");
	objs.push_back(m);

	for (double i = 0; i < objs.size(); i++)
	{
		if (i != 0)
			objs[i].translate_x = i / 5;
	}
}

void printw(float x, float y, float z, char* format, ...)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	va_list args;
	int len;
	int i;
	char * text;

	va_start(args, format);

	len = _vscprintf(format, args) + 1;
	text = (char *)malloc(len * sizeof(char));
	vsprintf_s(text, len, format, args);
	va_end(args);

	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos3f(x, y, z);
	for (i = 0; text[i] != '\0'; i++)
		glutBitmapCharacter(font_style, text[i]);
	free(text);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


void calculateFPS()
{
	frameCount++;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	int timeInterval = currentTime - previousTime;

	if (timeInterval > 1000)
	{
		fps = frameCount / (timeInterval / 1000.0f);
		previousTime = currentTime;
		frameCount = 0;
	}
}


void idle(void)
{
	calculateFPS();
	glutPostRedisplay();
}

// Red = Z , x = Blue, Y = Green
void drawGrid()
{
	glPushMatrix();
	glTranslatef(-0.5, -0.2, 0);
	glDisable(GL_LIGHTING);
	glColor3f(.3, .3, .3);
	glBegin(GL_LINES);
	for (double i = 0; i <= 1; i = i + 0.1)
	{
		if (i == 0) { glColor3f(.6, .3, .3); }
		else { glColor3f(.25, .25, .25); };
		glVertex3f(i, 0, 0);
		glVertex3f(i, 0, 1);

		if (i == 0) { glColor3f(.3, .3, .6); }
		else { glColor3f(.25, .25, .25); };
		glVertex3f(0, 0, i);
		glVertex3f(1, 0, i);

	};

	for (double i = 0; i <= 1; i = i + 0.1)
	{
		glColor3f(.25, .25, .25);
		glVertex3f(0, i, 1);
		glVertex3f(1, i, 1);

		if (i == 0) { glColor3f(.3, .6, .3); }
		else { glColor3f(.25, .25, .25); };
		glVertex3f(i, 0, 1);
		glVertex3f(i, 1, 1);

	};

	glEnd();
	glPopMatrix();
}

void handleKeypress(unsigned char key, int x, int y)
{
	switch (key){
	case 43://+
		if (!lightSelected)
			objs[modelIndex].scale += 0.001;
		break;
	case 61://=
		if (!lightSelected)
			objs[modelIndex].scale += 0.001;
		break;
	case 45://-
		if (!lightSelected && objs[modelIndex].scale>0)
			objs[modelIndex].scale -= 0.001;
		break;
	case 95://_
		if (!lightSelected && objs[modelIndex].scale>0)
			objs[modelIndex].scale -= 0.001;
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
		cameraPrincipal.translateLoc(0, 0, 0.01);
		break;

	case 115: //s
		cameraPrincipal.translateLoc(0, 0, -0.01);
		break;

	case 97: //a
		cameraPrincipal.translateLoc(-0.01, 0, 0);
		break;

	case 100: //d
		cameraPrincipal.translateLoc(0.01, 0, 0);
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

void myreshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	wWidth = w;
	wHeight = h;
	double g_Width = wWidth;
	double g_Height = wHeight;
	glViewport(0, 0, g_Width, g_Height);
	glLoadIdentity();
	gluPerspective(45, g_Width / g_Height, 0.1f, 500.0f);
}

//select: x = 0; y = 1 ; z=2;
void translateModel(int selector, double deslocamento)
{
	const double translateLightBoost = 0.10;
	if (selector == 0)
	{
		if (!lightSelected)
		{
			objs[modelIndex].translate_x += deslocamento;
		}
		else{
			if (lightIndex == 0)
			{
				L1.translate(deslocamento + translateLightBoost, 0, 0);
			}
			else{
				L2.translate(deslocamento + translateLightBoost, 0, 0);
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
	else if (selector == 2){
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
	if (modelIndex < objs.size() - 1 && !lightSelected)
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
			cameraPrincipal.rotateLoc((x - mousepos_x)*0.2, 0, 1, 0);
			cameraPrincipal.rotateGlob((y - mousepos_y)*0.2, 1, 0, 0);
		}
		mousepos_x = x;
		mousepos_y = y;
	}
}

int main(int argc, char* argv[]){

	LoadModels();
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wWidth, wHeight);
	glutCreateWindow("Projeto PG");

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(myreshape);
	glutMotionFunc(mouseMotion);
	glutMouseFunc(mouseClickFunction);

	glutMainLoop();

	return 0;
}
