#include "Controladora.h"
#include "Jugador.h"


CControladora::CControladora() {
	cancha = new CCancha();
	jugador = new CJugador(ANCHOIMAGEN, ALTOIMAGEN);
	bombas = new CColeccionBomba();
	habilidades = new CColeccionHabilidad();
	enemigos = new CColeccionEnemigo();
	nivel = 3;
}

int CControladora::getNivel() {
	return nivel;
}

void CControladora::setNivel(int nivel) {
	this->nivel = nivel;
}

void CControladora::inicializar() {
	cancha->Inicializar();
}

void CControladora::Dibujar() {
	cancha->Inicializar();
};
void CControladora::dibujarCancha(Graphics^ g, Bitmap^ bmpPiso, Bitmap^ bmpIrrompible, Bitmap^ bmpRrompible, Bitmap^ bmpHabilidad) {
	cancha->PintarCancha(g, bmpPiso);
	cancha->PintarMatriz(g, bmpIrrompible, bmpRrompible);
	habilidades->dibujar(g, bmpHabilidad, cancha->getCancha());
};

void CControladora::dibujarJugador(Graphics^ g, Bitmap^ bmpJugador) {
	jugador->dibujar(g, bmpJugador, cancha->getCancha());
}

void CControladora::adicionarBomba() {
	bombas->crearBomba(jugador->getX(), jugador->getY());
}

void CControladora::moverJugador(Graphics^ g, Bitmap^ bmpJugador, Bitmap^ bmpBomba, Bitmap^ bmpExplosion, Bitmap^ bmpEnemigo) {
	bombas->dibujarBomba(g, bmpBomba, bmpExplosion, jugador->getX(), jugador->getY(), cancha->getCancha());
	jugador->mover(g, bmpJugador, cancha->getCancha());
	enemigos->dibujar(g, bmpEnemigo, cancha->getCancha());
}

CJugador* CControladora::getJugador() {
	return jugador;
}

void CControladora::crearHabilidades() {
	while (habilidades->getHabilidades().size() < nivel) {
	  habilidades->crearHabilidad();
	}
}

void CControladora::crearEnemigos() {
	//enemigos->buscarEspacioLibre(cancha->getCancha());
	while (enemigos->getEnemigos().size() < nivel) {
		enemigos->crearEnemigo();
	}
}

CColeccionHabilidad* CControladora::getColeccionHabilidades() {
	return habilidades;
}

CColeccionEnemigo* CControladora::getColeccionEnemigos() {
	return enemigos;
}

// Controladora.h
#ifndef CONTROLADORA_H
#define CONTROLADORA_H

class Controladora {
public:
    void usarHabilidad(int tipo);

	// controladora.cpp
	void Controladora::usarHabilidad(int tipo, Jugador& jugador, Bomba& bomba) {
		switch (tipo) {
		case 1: // Bomba
			jugador.adicionarTotalBombas(1);
			break;
		case 2: // Fuego
			bomba.aumentarRangoExplosion();
			break;
		case 3: // Quitar vida
			jugador.disminuirVida();
			// Si vidas == 0, llama a reiniciarNivel o terminarJuego
			break;
		case 4: // Mayor velocidad
			jugador.aumentarVelocidad(2); // O el valor que desees
			break;
		case 5: // Aumentar vida
			jugador.incrementarVida();
			break;
		}
	}

};

#endif
// Controladora.h
#ifndef CONTROLADORA_H
#define CONTROLADORA_H

class Controladora {
public:
	void usarHabilidad(int tipo);
};

#endif
