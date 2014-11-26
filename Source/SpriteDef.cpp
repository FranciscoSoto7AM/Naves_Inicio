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
	modulos[3].x = 179;
	modulos[3].y = 44;
	modulos[3].w = 235;
	modulos[3].h = 52;

	modulos[4].id = MODULO_FondoMenu_NOMBRE;
	modulos[4].x = 16;
	modulos[4].y = 425;
	modulos[4].w = 157;
	modulos[4].h = 24;

	modulos[5].id = MODULO_FondoMenu_MENU_OPCION1;
	modulos[5].x = 369;
	modulos[5].y = 160;
	modulos[5].w = 99;
	modulos[5].h = 28;

	modulos[6].id = MODULO_FondoMenu_MENU_OPCION2;
	modulos[6].x = 368;
	modulos[6].y = 195;
	modulos[6].w = 56;
	modulos[6].h = 29;

	modulos[7].id = MODULO_FondoMenu_MENU_OPCION1_SELECCIONADO;
	modulos[7].x = 367;
	modulos[7].y = 232;
	modulos[7].w = 100;
	modulos[7].h = 29;

	modulos[8].id = MODULO_FondoMenu_MENU_OPCION2_SELECCIONADO;
	modulos[8].x = 366;
	modulos[8].y = 271;
	modulos[8].w = 60;
	modulos[8].h = 27;



};
