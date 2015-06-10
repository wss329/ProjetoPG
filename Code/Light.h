#include <iostream>

using namespace std;

struct Points{
	float x;
	float y;
	float z;
};

class Light
{
public:
	bool on;
	Points pontos;
	Light();
	void translate(float Ex, float Ey, float Ez);
};