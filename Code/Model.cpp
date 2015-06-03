// obj armazenado aqui por estruturas de dados, e funções de deslocamento etc...

#include "Model.h"

Model::Model(const char* path)
{
	hasTexture = false;
	hasNormal = false;

	
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
			if (!hasTexture && !hasNormal)
			{
				//ler no formato f v v v v... calcular normais e salva-las
			}
			else if (hasTexture && !hasNormal)
			{
				//ler no formato f v/vt/ v/vt/ v/vt/ ... calcular normais e salva-las
				//provavelmente não é formato aceitável
			}
			else if (hasTexture && hasNormal)
			{
				//ler e salvar no formato f v/vt/vn v/vt/vn v/vt/vn ...
			}
			else if (!hasTexture && hasNormal)
			{
				//ler e salvar no formato f v//vn v//vn v/t/vn ...
			}
		}
	}
		
}

void Model::LoadNurb(const char* filename)
{
	//ler a documentação do nurb
}

void Model::DrawModel()
{
	//desenhar o modelo na tela
}