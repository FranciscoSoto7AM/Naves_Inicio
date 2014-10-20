#include <SDL.h>
#include "Sprite.h"

class CGame
{
public:
	bool Start();
	enum Estado{
		ESTADO_INICIANDO,
		ESTADO_MENU,
		ESTADO_JUGANDO,
		ESTADO_TERMINANDO,
		ESTADO_FINALIZADO
	};
	
	static CGame instanceGame;

	CGame();
	void Finalize();

private:
	void Iniciando();
	SDL_Surface *screen;
	Sprite *nave;
	Estado estado;   
};