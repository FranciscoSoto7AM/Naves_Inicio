#include "Nave.h"

Nave::Nave(SDL_Surface * screen, char * rutaImagen, int x, int y, int module)
{
	nave = new Objeto(screen, rutaImagen, x, y, module);


}
void Nave::Pintar()
{
	nave->Pintar();

}
void Nave::MoverAbajo()
{
	nave->MoverY(5);
}
void Nave::MoverArriba()
{
	nave->MoverY(-5);
}
void Nave::MoverDerecha()
{
	nave->MoverX(5);
}
void Nave::MoverIzquierda()
{
	nave->MoverX(-5);
}
Objeto* Nave::GetNaveObjeto()
{
	return nave;
}