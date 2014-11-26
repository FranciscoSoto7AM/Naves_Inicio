
#ifndef _NAVE_H_
#define _nave_h_
#include "Objeto.h"

class Nave
{
	Objeto * nave;
	Objeto * bala;
public:
	Nave(SDL_Surface * screen, char * rutaImagen, int x, int y, int module);
	void Pintar();
	void MoverArriba();
	void MoverAbajo();
	void MoverDerecha();
	void MoverIzquierda();
	Objeto * GetNaveObjeto();


};

#endif





