#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "Objeto.h"
#include "Nave.h"

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
	
	Objeto *enemigoArreglo[10];

	Objeto *menu;  //fondo del menu
	Objeto *textos;    //texto del juego
	Objeto *fondo;   //fondo del juego


	int tick;
	int tiempoFrameInicial;
	int tiempoFrameFinal;

	Estado estado;   
};