#ifndef __Objeto_H__
#define __Objeto_H__
#include "Sprite.h"
#include <SDL.h>
class Objeto
{
	Sprite *sprite;
	int x;
	int y;
	int w;
	int h;
	bool autoMovimiento;
	int pasoActual;
	int pasoLimite;
	int module;  //modulo actual
public:
	void MoverX(int posicion);
	void MoverY(int posicion);
	Objeto(SDL_Surface * screen, char * rutaImagen, int x, int y, int module); //Constructor
	void SetAutoMovimiento(bool autoMovimiento);
	void SetPasoLimite(int pasos);
	int ObtenerPasoActual();
	void IncrementarPasoActual();
	bool EstaColicionando(Objeto * b);
	void Pintar();
	void Pintar(int module, int x, int y);
	void Actualizar();
	int ObtenerX();
	int ObtenerY();
	int ObtenerW();
	int ObtenerH();
};


#endif