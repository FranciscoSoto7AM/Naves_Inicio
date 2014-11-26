#ifndef __SPRITE_H__
#define __SPRITE_H__
#include <SDL.h>
#include "SpriteDef.h"


class Sprite{
	SDL_Surface * imagen;
	SDL_Surface * Screen;
	SpriteDef spriteDef;
public:
	Sprite(SDL_Surface * Screen);
	~Sprite(); //destructor
	void CargaImagen(char * path);
	void PintarModulo(int nombre, int x, int y);
	int WidthModule(int module);
	int HeightModule(int module);

};
#endif
