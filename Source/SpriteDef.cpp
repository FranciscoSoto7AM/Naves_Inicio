#include "SpriteDef.h"
# include "config.h"


SpriteDef::SpriteDef()
{

	modulos[0].id = MODULO_minave_NAVE;
	modulos[0].x = 0;
	modulos[0].y = 0;
	modulos[0].w = 64;
	modulos[0].h = 64;

	modulos[1].id = MODULO_FondoMenu_FONDO;
	modulos[1].x = 1;
	modulos[1].y = 0;
	modulos[1].w = WIDTH_SCREEN;
	modulos[1].h = HEIGHT_SCREEN;

	modulos[2].id = MODULO_enemigo_NAVE;
	modulos[2].x = 0;
	modulos[2].y = 0;
	modulos[2].w = 54;
	modulos[2].h = 61;

	modulos[3].id = MODULO_FondoTexto_TITULO;
	modulos[3].x = 9;
	modulos[3].y = 67;
	modulos[3].w = 277;
	modulos[3].h = 53;

	modulos[4].id = MODULO_FondoMenu_NOMBRE;
	modulos[4].x = 8;
	modulos[4].y = 184;
	modulos[4].w = 228;
	modulos[4].h = 55;

	modulos[5].id = MODULO_FondoMenu_MENU_OPCION1;
	modulos[5].x = 410;
	modulos[5].y = 47;
	modulos[5].w = 162;
	modulos[5].h = 54;

	modulos[6].id = MODULO_FondoMenu_MENU_OPCION2;
	modulos[6].x = 410;
	modulos[6].y = 119;
	modulos[6].w = 118;
	modulos[6].h = 50;

	modulos[7].id = MODULO_FondoMenu_MENU_OPCION1_SELECCIONADO;
	modulos[7].x = 410;
	modulos[7].y = 207;
	modulos[7].w = 160;
	modulos[7].h = 57;

	modulos[8].id = MODULO_FondoMenu_MENU_OPCION2_SELECCIONADO;
	modulos[8].x = 410;
	modulos[8].y = 279;
	modulos[8].w = 118;
	modulos[8].h = 49;



};
