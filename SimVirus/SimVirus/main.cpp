#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Simulador.h"
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;
#define CRT_SECURE_NO_WARNINGS 1 // para deshabilitar errores por uso de funciones deprecated sobre CRT o consola
#pragma warning(disable : 4996)
bool validaCntTics(int ct);
bool validaCntPersonas(int ct);
bool validaCntInfectados(int ct);
bool validaSize(int ct);
bool validaProInfec(double ct);
bool validaProbRec(double ct);
bool validaCntMuerte(int ct);

//#define DEBUG 1 // activa código de depuración
int main(int argc, char* argv[]) {
	int size, susceptiblesTic, personas, infectados, totalTics, cntMuerte, susceptibles, muertos, recuperados;
	double potInfecc, potRecup;
	string nombreArchivo;
	double percInfec = 0.0;
	double percRecup = 0.0;
	double percMuertos = 0.0;
	double percSusceptibles = 0.0;
	infectados = muertos = susceptiblesTic = recuperados = susceptibles = 0;
	while (!validaCntInfectados(infectados) || !validaCntPersonas(personas) || !validaCntTics(totalTics) ||
		!validaProbRec(potRecup) || !validaProInfec(potInfecc) || !validaSize(size) || !validaCntMuerte(cntMuerte)) {
		cout << "Digite la cantidad de Personas" << endl;
		cin >> personas;
		cout << "Digite la cantidad de Infectados" << endl;
		cin >> infectados;
		cout << "Digite la cantidad de Tics Totales" << endl;
		cin >> totalTics;
		cout << "Digite la cantidad de Tics antes de la perdicion!!!!" << endl;
		cin >> cntMuerte;
		cout << "Digite el Potencial de Infeccion de 0.0 a 1.0" << endl;
		cin >> potInfecc;
		cout << "Digite el Potencial de Recuperacion de 0.0 a 1.0 " << endl;
		cin >> potRecup;
		cout << "Escoja el tamaño de la civilizacion:" << endl;
		cout << "1) 35 X 35" << endl;
		cout << "2) 100 X 100" << endl;
		cout << "3) 500 X 500" << endl;
		cout << "4) 1000 X 1000" << endl;
		cin >> size;
	}
	switch (size)
	{
	case 1:
		size = 35;
		break;

	case 2:
		size = 100;
		break;

	case 3:
		size = 500;
		break;

	case 4:
		size = 1000;
		break;

	default:
		cout << "Holi k ac :v" << endl;
		break;
	}
	cout << "Digite el nombre de la bitacora" << endl;
	cin >> nombreArchivo;
	ofstream archivoSalida(nombreArchivo + ".txt");
	Simulador matrix(personas, infectados, cntMuerte, potInfecc, potRecup, size);
	archivoSalida << "Cantidades Originales." << endl;
	archivoSalida << "Personas Suceptibles: " << (personas - infectados) << endl;
	archivoSalida << "Infectados: " << (personas * infectados)/100 << endl;
	archivoSalida << "Cantidad de Tics: " << totalTics << endl;
	archivoSalida << "Tamaño de la civilizacion: " << size << " X " << size << endl;
	archivoSalida << omp_get_max_threads() << endl;
	infectados = muertos = susceptiblesTic = recuperados = susceptibles = 0;
	//inicia tiempo
	/*steady_clock::time_point iniciar;
	iniciar = steady_clock::now();*/
	steady_clock::time_point t1;
	steady_clock::time_point t2;
	duration<double> time_tic;
	duration<double> time_span;
	for (int i = 1; i <= totalTics; i++) {
		t1 = steady_clock::now();
		matrix.generarTic();
		matrix.calcularInfeciones();
		t2 = steady_clock::now();
		time_span += duration_cast<duration<double>>(t2 - t1);
		if (matrix.getCantInfect() == 0)
			time_tic = time_span;
		infectados += matrix.getCantInfect();
		muertos += matrix.getCantMuertos();
		recuperados += matrix.getCantRecup();
		susceptibles += personas - matrix.getCantMuertos() - matrix.getCantInfect() - matrix.getCantRecup();
		susceptiblesTic = personas - matrix.getCantMuertos() - matrix.getCantInfect() - matrix.getCantRecup();
		percSusceptibles = (susceptiblesTic * 100) / personas;
		percInfec = (matrix.getCantInfect() * 100) / personas;
		percMuertos = (matrix.getCantMuertos() * 100) / personas;
		percRecup = (matrix.getCantRecup() * 100) / personas;
		archivoSalida << "Dia: " << i << endl;
		archivoSalida << "Cantidad total de Susceptibles: " << susceptiblesTic << endl;
		archivoSalida << "Promedio de Personas Susceptibles: " << (double(susceptibles) / i) << endl;
		archivoSalida << "Porcentaje: " << percSusceptibles << endl;
		archivoSalida << "Cantidad total de Infectados: " << matrix.getCantInfect() << endl;
		archivoSalida << "Promedio de Personas Infectadas: " << (double(infectados) / i) << endl;
		archivoSalida << "Porcentaje: " << percInfec << endl;
		archivoSalida << "Cantidad total de Muertos: " << matrix.getCantMuertos() << endl;
		archivoSalida << "Promedio de Personas Muertas: " << (double(muertos) / i) << endl;
		archivoSalida << "Porcentaje: " << percMuertos << endl;
		archivoSalida << "Cantidad total de Recuperados: " << matrix.getCantRecup() << endl;
		archivoSalida << "Promedio de Personas Recuperadas: " << (double(recuperados) / i) << endl;
		archivoSalida << "Porcentaje: " << percRecup << endl;
		archivoSalida << endl;
	}
	//termina tiempo
	//steady_clock::time_point t2 = steady_clock::now();
	//imprime duracion
	//duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	archivoSalida << "Duracion para la estabilizacion: " << time_span.count() << " segundos." << endl;
	cout << "Duracion para la estabilizacion: " << time_span.count() << " segundos." << endl;
	archivoSalida << "Duracion total: " << time_span.count() << " segundos." << endl;
	std::cout << "Duracion total: " << time_span.count() << " segundos.";
	cin >> personas;
	return 0;
}

bool validaCntTics(int ct)
{
	bool valido = true;
	if(ct < 1)
		cout << "Por Favor Digite una cantidad Valida." << endl;
	return valido;
}

bool validaCntPersonas(int ct)
{
	bool valido = true;
	if(ct < 1)
		cout << "Por Favor Digite una cantidad Valida." << endl;
	return valido;
}

bool validaCntInfectados(int ct)
{
	bool valido = true;
	if(ct < 1)
		cout << "Por Favor Digite una cantidad Valida." << endl;
	return valido;
}

bool validaSize(int ct)
{
	bool succes = false;
	if (ct >= 1 && ct <= 3)
		succes = true;
	else
		cout << "Por Favor Digite una opcion valida." << endl;
	return succes;
}

bool validaProInfec(double ct)
{
	bool succes = false;
	if (ct > 0.0 && ct < 1.0)
		succes = true;
	else
		cout << "Por Favor Digite una probabilidad valida." << endl;
	return succes;
}

bool validaProbRec(double ct)
{
	bool succes = false;
	if (ct > 0.0 && ct < 1.0)
		succes = true;
	else
		cout << "Por Favor Digite una probabilidad valida." << endl;
	return succes;
}

bool validaCntMuerte(int ct)
{
	bool valido = true;
	if(ct < 1)
		cout << "Por Favor Digite una cantidad Valida." << endl;
	return valido;
}