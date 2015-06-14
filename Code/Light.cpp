#include "Light.h"

Light::Light(){
	on = false;
	pontos.x = 5;
	pontos.y = 5;
	pontos.z = 5;

}


void Light::translate(float Ex, float Ey, float Ez){
	pontos.x = pontos.x + Ex;
	pontos.y = pontos.y + Ey;
	pontos.z = pontos.z + Ez;
}
