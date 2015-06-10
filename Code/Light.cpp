#include "Light.h"

Light::Light(){
	on = false;
	pontos.x = 0;
	pontos.y = 0;
	pontos.z = 0;

}


void Light::translate(float Ex, float Ey, float Ez){
	pontos.x = pontos.x + Ex;
	pontos.y = pontos.y + Ey;
	pontos.z = pontos.z + Ez;
}
