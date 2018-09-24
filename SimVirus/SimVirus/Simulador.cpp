#include "Simulador.h"
#include <random>
#include <time.h>


Simulador::Simulador()
{
	//no usarse
}

Simulador::Simulador(int personas,int infectados, double potInfecc, double potRecup, int tamaño, int totalTics) {
	cantPersonas = personas;
	cantInfectados = infectados;
	probaInfec = potInfecc;
	probaRecup = potRecup;
	cantTics = totalTics;
	vector<int> filas;
	filas.resize(tamaño, 0);
	cuadriculaDeInfeccion.resize(tamaño, filas);
	ticActual = 0;
	cantMuertos = 0;
	cantRecuperados = 0;
	shared_ptr<Persona> ciudadano;
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, tamaño);
	int x, y;
	//Agregar la funcion que lo vuelve infeccioso, no creo que se pueda paralelizar el random.
	//Pensar si mejor crear un metodo para darle ubicacion o usar punteros, más pesado eso si.
#pragma omp parallel num_threads(omp_get_max_threads()) private(ciudadano,x,y)
	{
		for (int i = 0; i < personas; i++) {
			if (i < infectados) {
				x = distribution(generator);
				y = distribution(generator);
				ciudadano = shared_ptr<Persona>(new Persona(x,y,1));
#pragma omp critical
				civilizacion.push_back(ciudadano);
#pragma omp atomic
				cuadriculaDeInfeccion[x][y]++;
			}
			else
			{
				x = distribution(generator);
				y = distribution(generator);
				ciudadano = shared_ptr<Persona>(new Persona(x, y, 0));
#pragma omp critical
				civilizacion.push_back(ciudadano);
			}
		}
	}
}

Simulador::~Simulador()
{

}

void Simulador::setCantMuertos(int killThem) {
	cantMuertos = killThem;
}

void Simulador::setCantInfect(int spreadDis) {
	cantInfectados = spreadDis;
}

void Simulador::setCantRecup(int healThem) {
	cantRecuperados = healThem;
}

void Simulador::setCantPersonas(int giveBirth) {
	cantPersonas = giveBirth;
}

void Simulador::setProbaInfec(double infeccioso) {
	probaInfec = infeccioso;
}

void Simulador::setProbaRecup(double inmunidad) {
	probaRecup = inmunidad;
}

int Simulador::getCantMuertos() {
	return cantMuertos;
}

int Simulador::getCantInfect() {
	return cantInfectados;
}

int Simulador::getCantRecup() {
	return cantRecuperados;
}

int Simulador::getCantPersonas() {
	return cantPersonas;
}

double Simulador::getProbaInfec() {
	return probaInfec;
}

double Simulador::getProbaRecup() {
	return probaRecup;
}