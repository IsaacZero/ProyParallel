#include "Simulador.h"



Simulador::Simulador()
{
}

Simulador::Simulador(int personas, double potInfecc, double potRecup, int totTics, int tamaño) {
	cantPersonas = personas;
	probaInfec = potInfecc;
	probaRecup = potRecup;
	cantTics = totTics;
	//Agregar la funcion que lo vuelve infeccioso, no creo que se pueda paralelizar el random.
	//Pensar si mejor crear un metodo para darle ubicacion o usar punteros, más pesado eso si.
	/*bool bornInfected;
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, tamaño);
	int X = distribution(generator);
	int Y = distribution(generator);
	Persona* ciudadano = new Persona(X, Y, bornInfected);
	civilizacion.resize(cantPersonas);*/
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