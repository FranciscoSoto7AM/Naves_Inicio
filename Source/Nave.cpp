#include "Nave.h"
#include "Config.h"


Nave::Nave(SDL_Surface * screen, char * rutaImagen, int x, int y, int module)
{
	nave = new Objeto(screen, rutaImagen, x, y, module);
	for (int i = 0; i<MAXIMO_DE_BALAS; i++){
		bala[i] = new Objeto(screen, "../Data/balas.bmp", 0, 0, MODULO_BALAS_BALA);
		bala[i]->SetVisible(false);
	}
	balaVisibles = 0;
	visible = true;
	colision = false;
}
void Nave::CrearNuevo(){
	balaVisibles = 0;
	visible = true;
	colision = false;
	for (int i = 0; i<MAXIMO_DE_BALAS; i++){
		bala[i]->SetVisible(false);
	}
	nave->PonerEn(0, 0);//mover en x y y
}
void Nave::Pintar(int tipoNave){
	if (visible){
	nave->Pintar();
	for (int i = 0; i < MAXIMO_DE_BALAS; i++)
	{
		bala[i]->Pintar();
		switch (tipoNave)
		{
		case NAVE_PROPIA:
			bala[i]->MoverY(-10);
			break;

		case NAVE_ENEMIGO:
			bala[i]->MoverY(10);
			break;
		}
		}
	}
}
void Nave::Disparar(int tipoNave, int Balas){
	if (visible){
	bala[balaVisibles]->SetVisible(true);
	switch (tipoNave)
	{
	case NAVE_PROPIA:
		bala[balaVisibles]->PonerEn(nave->ObtenerX() + nave->ObtenerW() / 2, nave->ObtenerY());
		break;
	case NAVE_ENEMIGO:
		bala[balaVisibles]->PonerEn(nave->ObtenerX() + nave->ObtenerW() / 2, nave->ObtenerY() + nave->ObtenerH());
		break;
	}

	balaVisibles++;
	if (balaVisibles >= Balas)
		balaVisibles = 0;

	}
}

void Nave::MoverAbajo(int velocidad){ nave->MoverY(velocidad); }
void Nave::MoverArriba(int velocidad){ nave->MoverY(-velocidad); }
void Nave::MoverDerecha(int velocidad){ nave->MoverX(velocidad); }
void Nave::MoverIzquierda(int velocidad){ nave->MoverX(-velocidad); }

Objeto*Nave::GetNaveObjeto(){
	return nave;
}

void Nave::AutoDispara(int Balas){
	if ((rand() % 100)<1)
		Disparar(NAVE_ENEMIGO, Balas);
}
void Nave::setVisible(bool visible){
	this->visible = visible;
}
bool Nave::estaColicionandoConBala(Nave*nave){

	return colision;
}

void Nave::simularColision(bool colision){
	this->colision = colision;
}