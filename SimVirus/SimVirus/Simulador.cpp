#include "Simulador.h"


Simulador::Simulador()
{
	//no usarse
}

Simulador::Simulador(int personas, int infectados, int cntMuerte, double potInfecc, double potRecup, int tamaño) {
	cantPersonas = personas;
	cantInfectados = infectados;
	probaInfec = potInfecc;
	probaRecup = potRecup;
	ticsBeforeDoom = cntMuerte;
	civilizacion.reserve(personas);
	vector<int> filas;
	filas.resize(tamaño, 0);
	cuadriculaDeInfeccion.resize(tamaño, filas);
	cantMuertos = 0;
	cantRecuperados = 0;
	random_device rd;
	default_random_engine generator(rd());
	uniform_int_distribution<int> distribution(0, tamaño-1);
	int x, y;
	//Agregar la funcion que lo vuelve infeccioso, no creo que se pueda paralelizar el random.
	//Pensar si mejor crear un metodo para darle ubicacion o usar punteros, más pesado eso si.
#pragma omp parallel for num_threads(omp_get_max_threads()) private(x,y) //shared(civilizacion)
	for (int i = 0; i < personas; i++) {
		Persona ciudadano(0, 0, 0);
		x = distribution(generator);
		y = distribution(generator);
		ciudadano.setPosicion(x, y);
		if (i < infectados) {
			ciudadano.setEstado(1);
#pragma omp atomic
			cuadriculaDeInfeccion[x][y]++;
		}
#pragma omp critical
		civilizacion.push_back(ciudadano);

	}
}

Simulador::~Simulador()
{

}

void Simulador::generarTic() {
	int x, y;
	pair<int, int> location;
	random_device rd;
	default_random_engine generator(rd());
	uniform_int_distribution<int> distribution(0, 1);
#pragma omp parallel for num_threads(omp_get_max_threads()) private (x, y, location)// shared(civilizacion, cuadriculaDeInfeccion)
	for (int i = 0; i < civilizacion.size(); i++) {
		if (civilizacion[i].getEstado() < 3) {
			x = distribution(generator);
			if (x == 0)
				x = -1;
			y = distribution(generator);
			if (y == 0)
				y = -1;
			location = civilizacion[i].getPosicion();
			x = (x + location.first) % cuadriculaDeInfeccion.size();
			if (x == -1)
				x += cuadriculaDeInfeccion.size();
			y = (y + location.second) % cuadriculaDeInfeccion.size();
			if (y == -1)
				y += cuadriculaDeInfeccion.size();
			civilizacion[i].setPosicion(x, y);
			if (civilizacion[i].getEstado() == 1) {
#pragma omp atomic
				cuadriculaDeInfeccion[location.first][location.second]--;
#pragma omp atomic
				cuadriculaDeInfeccion[x][y]++;
			}
		}
	}
}

void Simulador::calcularInfeciones() {
	int contador;
	double x;
	random_device rd;
	default_random_engine generator(rd());
	uniform_real_distribution<double> distribution(0.0, 1.0);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(x,contador)// shared(cantMuertos,cantRecuperados,cantInfectados,civilizacion,cuadriculaDeInfeccion)
	for (int i = 0; i < civilizacion.size(); i++) {
		if (civilizacion[i].getEstado() == 0 && (cuadriculaDeInfeccion[civilizacion[i].getPosicion().first][civilizacion[i].getPosicion().second] > 0)) {
			contador = cuadriculaDeInfeccion[civilizacion[i].getPosicion().first][civilizacion[i].getPosicion().second];
			while (civilizacion[i].getEstado() != 0 && (contador > 0)) {
				x = distribution(generator);
				if (x <= probaInfec) {
					civilizacion[i].setEstado(1);
#pragma omp atomic
					cuadriculaDeInfeccion[civilizacion[i].getPosicion().first][civilizacion[i].getPosicion().second]++;
#pragma omp atomic
					cantInfectados++;
				}
				contador--;
			}
		}
		else if (civilizacion[i].getEstado() == 1) {
			x = distribution(generator);
			if (x <= probaRecup) {
				civilizacion[i].setEstado(2);
#pragma omp atomic
				cantRecuperados++;
#pragma omp atomic
				cantInfectados--;
#pragma omp atomic
				cuadriculaDeInfeccion[civilizacion[i].getPosicion().first][civilizacion[i].getPosicion().second]--;
			}
			else
				civilizacion[i].setContadorEnfermo(civilizacion[i].getContadorEnfermo() + 1);
			if (civilizacion[i].getContadorEnfermo() == ticsBeforeDoom) {
				civilizacion[i].setEstado(3);
#pragma omp atomic
				cantMuertos++;
#pragma omp atomic
				cantInfectados--;
#pragma omp atomic
				cuadriculaDeInfeccion[civilizacion[i].getPosicion().first][civilizacion[i].getPosicion().second]--;
			}
		}
	}
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

void Simulador::setTicsBeforeDoom(int prophecy)
{
	ticsBeforeDoom = prophecy;
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

int Simulador::getTicsBeforeDoom()
{
	return ticsBeforeDoom;
}

double Simulador::getProbaInfec() {
	return probaInfec;
}

double Simulador::getProbaRecup() {
	return probaRecup;
}