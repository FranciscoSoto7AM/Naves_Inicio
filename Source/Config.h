// #pragma once   solo funciona con algunos windows no funciona con linux
#ifndef __CONFIG_H__   //funciona con todos los sistemas operativos
#define __CONFIG_H__   // es para que corra solo una vez el archivo .h
#define WIDTH_SCREEN 640   //define el ancho de la pantalla
#define HEIGHT_SCREEN 480  //define el largo de la pantalla

#define BORDE_IZQUIERDO 1<<0
#define BORDE_SUPERIOR  1<<1
#define BORDE_DERECHO   1<<2
#define BORDE_INFERIOR  1<<3

#define FPS_LIMIT   30.0f
#define FPS_DELAY   1000.0f / FPS_LIMIT

/*** SPRITES ***/
//#TIPO_IMAGEN_NOMBRE

#define MODULO_minave_NAVE                                0
#define MODULO_FondoMenu_FONDO                            1
#define MODULO_enemigo_NAVE                               2
#define MODULO_FondoTexto_TITULO                          3
#define MODULO_FondoMenu_NOMBRE                           4
#define MODULO_FondoMenu_MENU_OPCION1                     5
#define MODULO_FondoMenu_MENU_OPCION2                     6
#define MODULO_FondoMenu_MENU_OPCION1_SELECCIONADO        7
#define MODULO_FondoMenu_MENU_OPCION2_SELECCIONADO        8


#endif

