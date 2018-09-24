#pragma once
#include <vector>
#include <omp.h>
#include "Persona.h"
#include <random>
#include <list>
#include <utility>

class Simulador
{
public:
	Simulador();
	Simulador(int personas,int infectados, double potInfecc, double potRecup, int tamaño, int totalTics);
	virtual ~Simulador();

	//EFE: Realiza los movimientos en un tic.
	//REQ: Simulador inicializado.
	//MOD: cuadriculaDeInfeccion, la civilizacion change for ever.
	void generarTic();

	//EFE: Calcula los nuevos infectados, curados y muertos.
	//REQ: Simulador inicializado.
	//MOD: cuadriculaDeInfectados y la civilizacion.
	void calcularInfeciones();
	
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
	list<Persona> civilizacion;
	vector<vector<int>> cuadriculaDeInfeccion;
	int cantTics;
	int ticActual;
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

