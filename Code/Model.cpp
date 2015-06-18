#include "Model.h"

Model::Model(const char* path)
{
	hasTexture = false;
	hasNormal = false;
	
	string arquivo = path;
	size_t posPonto = arquivo.find_last_of(".");
	size_t posBarra = arquivo.find_last_of("/");
	nome = arquivo.substr(posBarra +1);
	string tipo = arquivo.substr(posPonto + 1);
	
	if (tipo.compare("obj") == 0)
		LoadObj(path);
	else if (tipo.compare("nurb") == 0)
		LoadNurb(path);
	else
		printf("%s \n", "Model type not recognised");
}

void Model::LoadObj(const char* path)
{
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
		else if (strcmp(line, "#") == 0)
		{
			// é comentário ignorar a linha
			//#vt e no f ele lê vt realmente não entendo isso...
		}
		else if (strcmp(line, "f") == 0)
		{
			int vert, text, norm;
			if (!hasTexture && !hasNormal)
			{
				Face novaface;
				int i = 1;
				while (i){
					if (i == EOF)
						break;
					i = fscanf(file, "%i", &vert);
					if (i!=0)
					novaface.vertices.push_back(vert);
				}
				faces.push_back(novaface);
				//ler no formato f v v v v... calcular normais e salva-las
			}
			else if (hasTexture && !hasNormal)
			{
				Face novaface;
				int i = 1;
				while (i>=1){
					if (i == EOF)
						break;
					i = fscanf(file, "%i/%i", &vert, &text);
					if (i != 0)
					{
					novaface.vertices.push_back(vert);
					novaface.texturas.push_back(text);
					}
				}
				faces.push_back(novaface);
				//ler no formato f v/vt/ v/vt/ v/vt/ ... calcular normais e salva-las
				//provavelmente não é formato aceitável
			}
			else if (hasTexture && hasNormal)
			{
				Face novaface;
				int i = 1;
				while (i>=1){
					if (i == EOF)
						break;
					i = fscanf(file, "%i/%i/%i", &vert, &text, &norm);
					if (i != 0)
					{
						novaface.vertices.push_back(vert);
						novaface.texturas.push_back(text);
						novaface.normais.push_back(norm);
					}
				}
				faces.push_back(novaface);
				//ler e salvar no formato f v/vt/vn v/vt/vn v/vt/vn ...
			}
			else if (!hasTexture && hasNormal)
			{
				Face novaface;
				int i = 1;
				while (i >= 1){
					if (i == EOF)
						break;
					i = fscanf(file, "%i//%i", &vert, &norm);
					if (i != 0)
					{
						novaface.vertices.push_back(vert);
						novaface.normais.push_back(norm);
					}
				}
				faces.push_back(novaface);
				//ler e salvar no formato f v//vn v//vn v/t/vn ...
			}
		}
	}
		if (!hasNormal)
		calcularNormal();
		
}

void Model::LoadNurb(const char* filename)
{
	//ler a documentação do nurb
}

void Model::DrawModel()
{
	glPushMatrix();

	// Transformações
	glTranslatef(translate_x, translate_y, translate_z);
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);
	glScalef(scale, scale, scale);

	if (!hasNormal)
	{
		for (size_t i = 0; i < faces.size(); i++)
		{
			Vector n = normais[i];
			glNormal3f(n.x, n.y, n.z);
			glBegin(GL_POLYGON);
			for (size_t t = 0; t < faces[i].vertices.size(); t++)
			{
				Vector v = vertices[faces[i].vertices[t] - 1];
				glVertex3f(v.x, v.y, v.z);
			}
			glEnd();
		}
	
	}
	else
	{
		for (size_t i = 0; i < faces.size(); i++)
		{
			glBegin(GL_POLYGON);

			for (size_t t = 0; t < faces[i].normais.size(); t++)
			{
				Vector n = normais[faces[i].normais[t] - 1];
				glNormal3f(n.x, n.y, n.z);
				Vector v = vertices[faces[i].vertices[t] - 1];
				glVertex3f(v.x, v.y, v.z);
			}

			//for (size_t t = 0; t < face.vertices.size(); t++)
			//{
			//	Vector v = vertices[face.vertices[t] - 1];
			//	glVertex3f(v.x, v.y, v.z);
			//}
			glEnd();
		}
	}
	glPopMatrix();
}

void Model::calcularNormal()
{
	for (size_t i = 0; i < faces.size(); i++)
	{
		Vector p1 = vertices[faces[i].vertices[0] - 1];
		Vector p2 = vertices[faces[i].vertices[1] - 1];
		Vector p3 = vertices[faces[i].vertices[2] - 1];

		normais.push_back( getNormal(p1, p2, p3));// tava normais[i+1] pensar depois
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