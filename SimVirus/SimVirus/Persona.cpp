#include "Persona.h"

Persona::Persona()
{
}

Persona::Persona(int X, int Y, bool bornInfected) {
	infectado = bornInfected;
	posicion = make_pair(X, Y);
}

Persona::~Persona()
{
}

void Persona::setCurado(bool estado) {
	curado = estado;
}

void Persona::setInfectado(bool estado) {
	infectado = estado;
}

void Persona::setMuerto(bool estado) {
	muerto = estado;
}

void Persona::setPosicion(int X, int Y) {
	posicion = make_pair(X, Y);
}

bool Persona::getCurado() {
	return curado;
}

bool Persona::getInfectado() {
	return infectado;
}

bool Persona::getMuerto() {
	return muerto;
}

pair<int,int> Persona::getPosicion() {
	return posicion;
}