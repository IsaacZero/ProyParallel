#pragma once
#include <vector>
#include <omp.h>
#include "Persona.h"
#include <random>

class Simulador
{
public:
	Simulador();
	Simulador(int personas, double potInfecc, double potRecup, int totTics, int tama�o);
	virtual ~Simulador();

	//EFE: Cambia la cantidad de muertos en el vector de personas.
	//MOD: Int cantMuertos.
	void setCantMuertos(int killThem);

	//EFE: Cambia la cantidad de infectados en el vector.
	//MOD: Int cantInfectados.
	void setCantInfect(int spreadDis);
	
	//EFE: Cambia la cantidad de personas curadas en el vector.
	//MOD: Int cantRecuperados.
	void setCantRecup(int healThem);
	
	//EFE: Cambia la cantidad de persona en el vector.
	//MOD: Int cantPersonas.
	void setCantPersonas(int giveBirth);
	
	//EFE: Cambia el porcentaje de infeccion.
	//MOD: Double probaInfec.
	void setProbaInfec(double infeccioso);

	//EFE: Cambia el porcentaje de recuperacion.
	//MOD: Double probaRecup.
	void setProbaRecup(double inmunidad);

	//EFE: Retorna cantMuertos.
	int getCantMuertos();
	
	//EFE: Retorna cantInfectados.
	int getCantInfect();
	
	//EFE: Retorna cantRecuperados.
	int getCantRecup();
	
	//EFE: Retorna cantPersonas.
	int getCantPersonas();

	//EFE: Retorna la probabilidad de Infeccion.
	double getProbaInfec();

	//EFE: Retorna la probabilidad de Recuperacion.
	double getProbaRecup();

private:
	vector<Persona> civilizacion;
	int cantTics;
	double probaInfec;
	double probaRecup;
	double promInfec;
	double promRecup;
	double promMuertos;
	double promCantPersonas;
	int cantMuertos;
	int cantInfectados;
	int cantRecuperados;
	int cantPersonas;
};

