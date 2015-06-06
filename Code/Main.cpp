#include "Model.h"
#include "openGL_tutorial.h"
#include <iostream>
#include <vector>


const int WINDOW_W = 500;
const int WINDOW_H = 500;

using namespace std;

vector <Model> objetos;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);	

	for (size_t i = 0; i < objetos.size(); i++)
	{
		objetos[i].DrawModel();
	}

	glFlush();
}

//void reshape(int w, int h)
//{
//	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0.0f, WINDOW_W, WINDOW_H, 0.0f, -5.0, 5.0);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//}

void handleKeypress(unsigned char key, int x, int y)
{
	static int x1 = 0;
	switch (key){
	case 27: // ESC
		exit(0);
		break;
	}
}
void LoadModels()
{
	Model m = new Model('dedo no cu');
	// adiciona os modelos no vector
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(0, 0); // a janela irá iniciar to topo esquerdo
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutCreateWindow("Projeto PG");
	LoadModels();

	//glMatrixMode(GL_MODELVIEW); // estou alterando a matrix de do modelo da cena
	//glLoadIdentity();

	glutDisplayFunc(display);
	glutKeyboardFunc(handleKeypress);
	//glutReshapeFunc(reshape);

	glutMainLoop();

	
}