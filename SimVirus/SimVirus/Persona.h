#pragma once
#include <utility>
#include <stdlib.h>

using namespace std;
class Persona
{
public:
	Persona();

	Persona(int X, int Y, bool bornInfected);

	virtual ~Persona();

	//EFE: Cambia el estado del bool muerto.
	//MOD: bool muerto.
	void setMuerto(bool estado);

	//EFE: Cambia el estado del bool curado.
	//MOD: bool curado.
	void setCurado(bool estado);

	//EFE: Cambia el estado del bool Infectado.
	//MOD: bool infectado.
	void setInfectado(bool estado);

	//EFE: Cambia la posicion de la persona.
	//MOD: Pair posicion.
	void setPosicion(int newX, int newY);

	//EFE: Cambia el contador de semanas que lleva una persona enferma
	//MOD: contadorEnfermo
	void setContadorEnfermo(int newContador);

	//EFE: Retorna true si la persona esta muerta o false en caso contrario.
	bool getMuerto();

	//EFE: Retorna true si la persona esta curada o false en caso contrario.
	bool getCurado();

	//EFE: Retorna true si la persona esta infectada o false en caso contrario.
	bool getInfectado();

	//EFE: Retorna el contador de semanas que lleva una persona enferma
	int getContadorEnfermo();

	//EFE: Retorna la posicion de la persona en un pair.
	pair<int, int> getPosicion();

private:
	bool muerto;
	bool curado;
	bool infectado;
	int contadorEnfermo;
	pair <int, int> posicion;
};