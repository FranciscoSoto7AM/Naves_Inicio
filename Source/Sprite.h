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
	~Sprite();
	void CargaImagen(char * path);
	void PintarModulo(int nombre, int x, int y, int w, int h);
	void PintarModulo(int nombre, int x, int y);

};


#endif
