#include <SDL.h>
#include "Sprite.h"
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
	void MoverEnemigo();
	bool EsLimitePantalla(Nave * objeto, int bandera);

	Uint8 *keys;
	SDL_Event event;
	SDL_Surface *screen;
	Nave * nave;
	
	Nave *enemigoArreglo[10];

	Nave *menu;  //fondo del menu
	Nave *textos;    //texto del juego
	Nave *fondo;   //fondo del juego

	int tick;
	int tiempoFrameInicial;
	int tiempoFrameFinal;

	Estado estado;   
};