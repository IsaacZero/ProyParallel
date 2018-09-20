#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Simulador.h"
#include <omp.h>

using namespace std;
#define CRT_SECURE_NO_WARNINGS 1 // para deshabilitar errores por uso de funciones deprecated sobre CRT o consola
#pragma warning(disable : 4996)

//#define DEBUG 1 // activa código de depuración
int main(int argc, char* argv[]) {
	int cantPersonas;

	cantPersonas = omp_get_max_threads();
	
	cout << cantPersonas << endl;
	cin >> cantPersonas;
	return 0;
}