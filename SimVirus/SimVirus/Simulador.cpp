#include "Simulador.h"


Simulador::Simulador()
{
	//no usarse
}

Simulador::Simulador(int personas,int infectados, double potInfecc, double potRecup, int tama�o, int totalTics) {
	cantPersonas = personas;
	cantInfectados = infectados;
	probaInfec = potInfecc;
	probaRecup = potRecup;
	cantTics = totalTics;
	vector<int> filas;
	filas.resize(tama�o, 0);
	cuadriculaDeInfeccion.resize(tama�o, filas);
	ticActual = 0;
	cantMuertos = 0;
	cantRecuperados = 0;
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, tama�o);
	int x, y;
	//Agregar la funcion que lo vuelve infeccioso, no creo que se pueda paralelizar el random.
	//Pensar si mejor crear un metodo para darle ubicacion o usar punteros, m�s pesado eso si.
#pragma omp parallel num_threads(omp_get_max_threads()) private(x,y) shared(civilizacion)
	{
		for (int i = 0; i < personas; i++) {
			if (i < infectados) {
				x = distribution(generator);
				y = distribution(generator);
				Persona ciudadano(x, y, 1);
#pragma omp critical
				civilizacion.push_back(ciudadano);
#pragma omp atomic
				cuadriculaDeInfeccion[x][y]++;
			}
			else
			{
				x = distribution(generator);
				y = distribution(generator);
				Persona ciudadano(x, y, 0);
#pragma omp critical
				civilizacion.push_back(ciudadano);
			}
		}
	}
}

Simulador::~Simulador()
{

}

void Simulador::generarTic() {
	int x, y;
	pair<int, int> location;
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, 1);
#pragma omp parallel for(omp_get_max_threads()) private (x, y, location) shared(civilizacion, cuadriculaDeInfeccion)
	for (list<Persona>::iterator it = civilizacion.begin(); it != civilizacion.end(); ++it){
		if (it->getEstado() < 3) {
			x = distribution(generator);
			if (x == 0)
				x = -1;
			y = distribution(generator);
			if (y == 0)
				y = -1;
			location = it->getPosicion();
			x = (x + location.first) % cuadriculaDeInfeccion.size();
			if (x == -1)
				x += cuadriculaDeInfeccion.size();
			y = (y + location.second) % cuadriculaDeInfeccion.size();
			if (y == -1)
				y += cuadriculaDeInfeccion.size();
			it->setPosicion(x, y);
			if (it->getEstado() == 1) {
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
	default_random_engine generator;
	uniform_real_distribution<double> distribution(0.0, 1.0);
#pragma omp parallel for(omp_get_max_threads()) private(x,contador) shared(civilizacion,cuadriculaDeInfeccion)
	for (list<Persona>::iterator it = civilizacion.begin(); it != civilizacion.end(); ++it) {
		if (it->getEstado() == 0 && (cuadriculaDeInfeccion[it->getPosicion().first][it->getPosicion().second] > 0)){
			contador = cuadriculaDeInfeccion[it->getPosicion().first][it->getPosicion().second];
			while (it->getEstado() != 0 && (contador > 0)) {
				x = distribution(generator);
				if (x <= probaInfec)
					it->setEstado(1);
				contador--;
			}
		}
		else if (it->getEstado() == 1) {
			x = distribution(generator);
			if (x <= probaRecup)
				it->setEstado(2);
			else
				it->setContadorEnfermo(it->getContadorEnfermo()+1);
			if (it->getContadorEnfermo() == 20)
				it->setEstado(3);
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