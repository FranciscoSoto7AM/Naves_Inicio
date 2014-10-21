#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Config.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Sprite.h"





CGame::CGame(){
	estado = ESTADO_INICIANDO;
	atexit(SDL_Quit);
	
}

// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
	delete(nave);
	SDL_FreeSurface(screen);
	SDL_Quit();
}



void CGame::Iniciando()
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("Error %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	screen = SDL_SetVideoMode(WIDTH_SCREEN, HEIGHT_SCREEN, 24, SDL_HWSURFACE);
	if (screen == NULL)
	{
		screen = SDL_SetVideoMode(640, 480, 24, SDL_SWSURFACE);
	}
	if (screen == NULL)
	{
		screen = SDL_SetVideoMode(640, 480, 24, SDL_SWSURFACE);
	}
	if (screen == NULL)
	{
		printf("Error %s ", SDL_GetError());
		exit(EXIT_FAILURE);

		printf("Error %s ", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_WM_SetCaption("Mi Primer video Juego", NULL);

		nave = new Nave(screen, "../Data/minave.bmp", (WIDTH_SCREEN / 2) /*- (sprite->WidthModule(0) / 2)*/, (HEIGHT_SCREEN - 80) /*- sprite->HeightModule(0)*/);
		enemigo = new Nave(screen, "../Data/enemigo.bmp", 0, 0);
		enemigo->SetAutoMovimiento(true);
	}


	bool CGame::Start()
	{
		// Esta variable nos ayudara a controlar la salida del juego...
		int salirJuego = false;
		int i = 0;

		while (salirJuego == false)
		{

			//Maquina de estados
			switch (estado)
			{

			case Estado::ESTADO_INICIANDO: //inicializando
				printf("1.- Estado_Iniciando");
				Iniciando();
				estado = ESTADO_MENU;
				break;
			case Estado::ESTADO_MENU:	   //MENU
				if (i == 0)
				{
					printf("\n2. Estado_Menu");
					estado = ESTADO_JUGANDO;
					i = 1;
				}
				else
				{
					printf("\n2. Estado_Menu");
					estado = ESTADO_FINALIZADO;

				}
				break;
			case Estado::ESTADO_JUGANDO: //JUGAR
				enemigo->Actualizar();
				SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
				keys = SDL_GetKeyState(NULL);
				if (keys[SDLK_RIGHT])
				{
					nave->MoverX(1);

				}
				if (keys[SDLK_LEFT])
				{
					nave->MoverX(-1);
				}
				nave->Pintar();
				enemigo->Pintar();
				if (keys[SDLK_DOWN])
				{
			
					printf("\n3. Estado_Jugando");
					estado = ESTADO_TERMINANDO;
				}
				break;

			case Estado::ESTADO_TERMINANDO: //TERMINAR
				printf("\n\n4. Estado_Terminando");
				estado = ESTADO_FINALIZADO;
				break;

			case Estado::ESTADO_FINALIZADO:  //FINALIZAR
				printf("\n\n5. Estado_Finalizando");
				getchar();
				salirJuego = true;
				break;
			}
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT) { salirJuego = true; }     //    Si se detecta una salida 
				if (event.type == SDL_KEYDOWN) {} //   una dirección (abajo) del teclado.
			}
			SDL_Flip(screen);

		}
		return true;
}