// obj armazenado aqui por estruturas de dados, e funções de deslocamento etc...

#include "Model.h"

Model::Model(const char* path)
{
	hasTexture = false;
	hasNormal = false;
	LoadObj(path);
}

void Model::LoadObj(const char* path)
{
	//nome = path.substring() pegar o nome do obj
	//No main ao selecionar um modelo imprimir seu nome com a posição do vector 
	//em que ele ta no main
	FILE * file = fopen(path, "r");

	while (true)
	{
		char line[250];
		int res = fscanf(file, "%s", line);

		if (res == EOF)// EOF = end of file
			break;

		if (strcmp(line, "v") == 0)
		{
			Vector novaVertice;
			fscanf(file, "%f %f %f\n", &novaVertice.x, &novaVertice.y, &novaVertice.z);
			vertices.push_back(novaVertice);
		}
		
		else if (strcmp(line, "vt") == 0)
		{
			hasTexture = true;
			Texture novatextura;
			fscanf(file, "%f %f\n", &novatextura.x, &novatextura.y);
			textura.push_back(novatextura);
		}
		
		else if (strcmp(line, "vn") == 0)
		{
			hasNormal = true;
			Vector novaNormal;
			fscanf(file, "%f %f %f\n", &novaNormal.x, &novaNormal.y, &novaNormal.z);
			normais.push_back(novaNormal);
		}

		else if (strcmp(line, "f") == 0)
		{
			//procurar saber como determinar fim da linha com fscan e também o esquema de
			//2 vectors para cada escrito no tutorial
			float vert, text, norm;
			if (!hasTexture && !hasNormal)
			{
				Face novaface;
				while (fscanf(file, "%f", &vert)){
					novaface.vertices.push_back(vert);
				}
				faces.push_back(novaface);
				//ler no formato f v v v v... calcular normais e salva-las
			}
			else if (hasTexture && !hasNormal)
			{
				Face novaface;
				while (fscanf(file, "%f/%f", &vert, &text)){
					novaface.vertices.push_back(vert);
					novaface.texturas.push_back(text);
				}
				faces.push_back(novaface);
				//ler no formato f v/vt/ v/vt/ v/vt/ ... calcular normais e salva-las
				//provavelmente não é formato aceitável
			}
			else if (hasTexture && hasNormal)
			{
				Face novaface;
				while (fscanf(file, "%f/%f/%f", &vert, &text, &norm)){
					novaface.vertices.push_back(vert);
					novaface.texturas.push_back(text);
					novaface.normais.push_back(norm);
				}
				faces.push_back(novaface);
				//ler e salvar no formato f v/vt/vn v/vt/vn v/vt/vn ...
			}
			else if (!hasTexture && hasNormal)
			{
				Face novaface;
				while (fscanf(file, "%f//%f", &vert, &norm)){
					novaface.vertices.push_back(vert);

					novaface.normais.push_back(norm);
				}
				faces.push_back(novaface);
				//ler e salvar no formato f v//vn v//vn v/t/vn ...
			}
		}
		if (!hasNormal)
		calcularNormal();
	}
		
}

void Model::LoadNurb(const char* filename)
{
	//ler a documentação do nurb
}

void Model::DrawModel()
{
	if (!hasNormal)
	{
		
		for (int i = 0; i < faces.size(); i++)
		{
			Face face = faces[i];
			Vector n = normais[i + 1];
			glNormal3f(n.x, n.y, n.z);
			glBegin(GL_POLYGON);
			for (int i = 0; i < face.vertices.size(); i++)
			{
				Vector v = vertices[face.vertices[i] + 1];
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
		}
	
	}
	else
	
	{
		for (int i = 0; i < faces.size(); i++)
		{
			Face face = faces[i];
			for (int t = 0; t < face.normais.size(); t++)
			{
				Vector n = normais[face.normais[t] + 1];
				glNormal3f(n.x, n.y, n.z);
			}
			glBegin(GL_POLYGON);
			for (int i = 0; i < face.vertices.size(); i++)
			{
				Vector v = vertices[face.vertices[i] + 1];
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
		}
	}

}

void Model::calcularNormal()
{
	for (int i = 0; i < faces.size(); i++)
	{
		Vector p1 = vertices[faces[i].vertices[1] + 1];
		Vector p2 = vertices[faces[i].vertices[2] + 1];
		Vector p3 = vertices[faces[i].vertices[3] + 1];

		normais[i+1] = getNormal(p1, p2, p3);
		//calcular normal para cada face
	}

}

Vector Model::getNormal(Vector p1,Vector p2, Vector p3)
{
	Vector v1, v2,n;
	double len;

	/* Encontra vetor v1 */
	v1.x = p2.x - p1.x;
	v1.y = p2.y - p1.y;
	v1.z = p2.z - p1.z;

	/* Encontra vetor v2 */
	v2.x = p3.x - p1.x;
	v2.y = p3.y - p1.y;
	v2.z = p3.z - p1.z;

	/* Calculo do produto vetorial de v1 e v2 */
	n.x = (v1.y * v2.z) - (v1.z * v2.y);
	n.y = (v1.z * v2.x) - (v1.x * v2.z);
	n.z = (v1.x * v2.y) - (v1.y * v2.x);

	/* normalizacao de n */
	len = sqrt(n.x*n.x + n.y*n.y + n.z*n.z);
	n.x /= len;
	n.y /= len;
	n.z /= len;
	return n;
}