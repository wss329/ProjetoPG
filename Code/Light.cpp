#include "Light.h"

Light::Light(){
	on = false;
	pontos.x = 1;
	pontos.y = 1;
	pontos.z = 1;

}


void Light::translate(float Ex, float Ey, float Ez){
	pontos.x = pontos.x + Ex;
	pontos.y = pontos.y + Ey;
	pontos.z = pontos.z + Ez;
}
