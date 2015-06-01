/*
-----------------------------------------------------------------------------
OpenGL Tutorial
VOXAR Labs
Computer Science Center - CIn
Federal University of Pernambuco - UFPE
http://www.cin.ufpe.br/~voxarlabs

-----------------------------------------------------------------------------
*/

#include "openGL_tutorial.h"

#include <iostream>
#include <vector>

const int WINDOW_W = 500;
const int WINDOW_H = 500;

using namespace std;

class Ponto	
{
public:
	double x, y;
	Ponto(double x, double y) : x(x), y(y) {};

};

vector <Ponto> pontos; //vector de pontos de controle
vector <Ponto> curva; //vector de pontos da curva
int nVezes = 0; // int para saber o numero de pontos
bool hit = false;// boolean para saber se o botão direito pegou em um ponto
int hitpos;//posição do array na qual o ponto foi selecionado


//Como especificado na descrição do projeto na parte "Os pontos de controle podem ser movidos atravéz da interação com o mouse", Os pontos de controle podem ser movidos
//com o uso do botão DIREITO do mouse.


void display()
{
	_sleep(40);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	if (pontos.size() > 0)
	{
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 0.0f);
		for (int i = 0; i < pontos.size(); i++)
		{
			glVertex2d(pontos.at(i).x, pontos.at(i).y);
		}

		glEnd();
	}
	
	if (pontos.size() >= 2){
		glPointSize(1.0f);

		glBegin(GL_POINTS);
		glColor3f(1.0f, 1.0f, 0.0f);
		for (int i = 0; i < curva.size(); i++)
			glVertex2d(curva.at(i).x, curva.at(i).y);
		glEnd();


		glBegin(GL_LINE_STRIP);
		glColor3f(1.0f, 1.0f, 1.0f);
		for (int i = 0; i < curva.size(); i++){
			glVertex2d(curva.at(i).x, curva.at(i).y);
		}
			
		glEnd();
	}
	glFlush();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, WINDOW_W, WINDOW_H, 0.0f, -5.0, 5.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void handleKeypress(unsigned char key, int x, int y)
{
	static int x1 = 0;
	switch (key){
	case 27: // ESC
		exit(0);
		break;
	}
}

double fact(int a)
{
	int i;
	double produto;

	produto = 1.0f;
	for (i = a; i > 0; i--)
		produto *= (double)i;
	return produto;
}

void bezier(){
	
		int n = pontos.size() - 1;
		for (double t = 0; t <= 1; t += 0.01) //parametro t
		{
			Ponto novoPonto = Ponto(0, 0);

			for (int i = 0; i <= n; i++)
			{
				double x = 0;
				x = (fact(n) / fact(i));
				x *= 1/(fact(n - i));
				x *= pow((1 - t), (n - i));
				x *= pow(t, i);

				novoPonto.x += x*pontos[i].x;
				novoPonto.y += x*pontos[i].y;
			}
			curva.push_back(novoPonto);
		}
}

void handleMouse(int x, int y)
{
	if (hit)
	{
		pontos[hitpos] = Ponto(x, y);
		curva.clear();
		bezier();
	}
}

void handleMouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
			pontos.push_back(Ponto(x, y));
			printf("%d\n", nVezes++);// teste para numeros de pontos de controle
			curva.clear();
			if (pontos.size() > 1)
				bezier();
		
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		{	
			hit = false;
			for (int i = 0; i < pontos.size(); i++)
			{
				if (x >= (pontos[i].x - 5) && (x <= pontos[i].x + 5))
				{
					if (y >= (pontos[i].y - 5) && (y <= pontos[i].y + 5))
					{
						hit = true; //clicou em um ponto existente
						hitpos = i; //guarda o ponto encontrado
						break;
					}
				}
			}
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		hit = false; // se soltar o botão direito para de ajustar
	}

	glutPostRedisplay();  // avisa que a janela atual deve ser reimpressa
			
}

//int main(int argc, char ** argv)
//{
//	glutInit(&argc, argv);
//	glutInitWindowPosition(0, 0); // a janela irá iniciar to topo esquerdo
//	glutInitWindowSize(WINDOW_W, WINDOW_H);
//	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//
//	glutCreateWindow("Curva de Bezier");
//	glMatrixMode(GL_MODELVIEW); // estou alterando a matrix de do modelo da cena
//	glLoadIdentity();
//
//	glutDisplayFunc(display);
//	glutKeyboardFunc(handleKeypress);
//	glutMouseFunc(handleMouseClick);
//	glutMotionFunc(handleMouse);
//	glutReshapeFunc(reshape);
//
//	glutMainLoop();
//
//	return 0;
//}