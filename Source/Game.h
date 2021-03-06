#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "Objeto.h"
#include "Nave.h"
#include "Stage.h"

#define BORDE_IZQUIERDO  1<<0
#define BORDE_SUPERIOR   1<<1
#define BORDE_DERECHO    1<<2
#define BORDE_INFERIOR   1<<3


class CGame
{
public:
	bool Start();
	static CGame instanceGame;
	enum Estado{
		ESTADO_INICIANDO,
		ESTADO_MENU,
		ESTADO_PRE_JUGANDO,
		ESTADO_JUGANDO,
		ESTADO_TERMINANDO,
		ESTADO_FINALIZADO
	};
	

	CGame();
	void Finalize();

private:
	void Iniciando();
	void Menu();
	void MoverEnemigo();
	bool EsLimitePantalla(Objeto * objeto, int bandera);

	int opcionSeleccionada;
	Uint8 *keys;
	SDL_Event event;
	SDL_Surface *screen;
	Nave * nave;

	Nave *enemigoArreglo[10];
	stage nivel[4];
	void InicializandoStage();
	int NivelActual;
	
	

	Objeto *menu;  //fondo del menu
	Objeto *textos;    //texto del juego
	Objeto *fondo;   //fondo del juego


	int tick;
	int tiempoFrameInicial;
	int tiempoFrameFinal;

	int vida;
	int enemigosEliminados;
	Estado estado;   
};