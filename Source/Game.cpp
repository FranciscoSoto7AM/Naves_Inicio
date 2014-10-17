#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include <SDL.h>
#include <SDL_image.h>


CGame::CGame(){
	estado = ESTADO_INICIANDO;
	//ACT3: Mal, este codigo no va aqui. Va en el metodo Iniciando().
	//ACT3:Mal, Aqui no debes de iniciar el video, deb estar en un metodo aparte, controlado por tu estado ESTADO_INICIANDO
	//if (SDL_Init(SDL_INIT_VIDEO) < 0)
	//{
	//	printf("no se pudo iniciar SDL: %s\n", SDL_GetError());
	//	exit(EXIT_FAILURE);
	//}
	//screen = SDL_SetVideoMode(600, 480, 24, SDL_HWSURFACE);
	//if (screen == NULL)
	//{
	//	printf("no se puede inicializar el modo grafico: \n", SDL_GetError());
	//	exit(1);
	//	atexit(SDL_Quit);
	//}
	//SDL_WM_SetCaption("Mi Primer Juego", NULL);
	//// ACT3:Mal hasta aqui.
}

// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
	SDL_Quit();
}

//ACT3: Mal, falto crear este metodo.
void CGame::Iniciando(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("no se pudo iniciar SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	screen = SDL_SetVideoMode(600, 480, 24, SDL_HWSURFACE);
	if (screen == NULL)
	{
		printf("no se puede inicializar el modo grafico: \n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);
	SDL_WM_SetCaption("Mi Primer Juego", NULL);
}


bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;
          
	while (salirJuego == false){
            
		//Maquina de estados
		switch(estado){
		case Estado::ESTADO_INICIANDO: //INICIALIZAR
			Iniciando(); //ACT3: Mal, Esto debe estar habilitado
			{
				//nave=SDL_LoadBMP("../DATA/nave.bmp");			
				//nave = IMG_LoadJPG_RW(SDL_RWFromFile("../Data/umi.jpg", "rb"));
				//nave = IMG_LoadJPG_RW(SDL_RWFromFile("../Data/Tools.jpg", "rb"));
				//nave = IMG_LoadPNG_RW(SDL_RWFromFile("../Data/dados.png", "rb"));
				nave = IMG_LoadJPG_RW(SDL_RWFromFile("../Data/cuadro.jpg", "rb"));
			
				SDL_Rect fuente;
				fuente.x = 580;
				fuente.y = 380;
				fuente.w = 319;
				fuente.h = 19;
				SDL_Rect destino;
				destino.x = 100;
				destino.y = 100;
				destino.w = 100;
				destino.h = 100;

				SDL_BlitSurface(nave, &fuente, screen, &destino);
			}
			estado = ESTADO_MENU;
			break;
		case Estado::ESTADO_MENU:	   //MENU	
			break;
		case Estado::ESTADO_JUGANDO: //JUGAR
			break;
		case Estado::ESTADO_TERMINANDO: //TERMINAR
			break;
		case Estado::ESTADO_FINALIZADO:  //FINALIZAR
				salirJuego = true;
			break;
		};
		SDL_Flip(screen);
    }
	return true;
}
