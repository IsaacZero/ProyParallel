#pragma once
#include <utility>
#include <stdlib.h>

using namespace std;
class Persona
{
public:
	Persona();

	Persona(int X, int Y, int estadoInicial);

	virtual ~Persona();
	//EFE: Modifica el estado de la persona entre 0 y 3 donde 0 = sano, 1 = infectado, 2 = immune, 3 = muerto;
	//MOD: estado
	void setEstado(int nuevoEstado);
	//EFE:cambia el contador de enfermo
	//MOD:contadorEnfermo
	void setContadorEnfermo(int nuevoContadorEnfermo);
	//EFE: Cambia la posicion del par ordenado
	//MOD: posicion
	void setPosicion(int x, int y);
	//EFE: Retorna el estado actual de la persona
	int getEstado();
	//EFE: Retorna el contador de semanas que lleva una persona enferma
	int getContadorEnfermo();
	//EFE: Retorna la posicion de la persona en un pair.
	pair<int, int> getPosicion();


private:
	int estado;//0 y 3 donde 0 = sano, 1 = infectado, 2 = immune, 3 = muerto;
	int contadorEnfermo;
	pair <int, int> posicion;
};