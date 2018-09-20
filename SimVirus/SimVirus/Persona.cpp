#include "Persona.h"

Persona::Persona()
{

}

Persona::Persona(int X, int Y, int estadoInicial) {
	estado = estadoInicial;
	posicion = make_pair(X, Y);
}

Persona::~Persona()
{
}

void Persona::setEstado(int nuevoEstado)
{
	estado = nuevoEstado;
}



int Persona::getContadorEnfermo()
{
	return contadorEnfermo;
}

void Persona::setContadorEnfermo(int newContador)
{
	contadorEnfermo = newContador;
}

void Persona::setPosicion(int x, int y)
{
	posicion = make_pair(x, y);
}

int Persona::getEstado()
{
	return estado;
}

pair<int,int> Persona::getPosicion() {
	return posicion;
}