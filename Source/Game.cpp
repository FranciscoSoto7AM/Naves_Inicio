#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Config.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Sprite.h"


// maestro este es el bueno para el examen


CGame::CGame(){
	estado = ESTADO_INICIANDO;
	atexit(SDL_Quit);
	
}

// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
	delete(nave);
	//delete(keys);
	delete *enemigoArreglo;
	SDL_FreeSurface(screen);
	SDL_Quit();

}



void CGame::Iniciando()  //iniciando
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
		

		for (int i = 0; i < 10; i++)
		{
			enemigoArreglo[i] = new Nave(screen, "../Data/enemigo.bmp",i* 60, 0);
			enemigoArreglo[i]->SetAutoMovimiento(false);
			enemigoArreglo[i]->SetPasoLimite(4);
		}
		
		

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
				
				for (int i = 0; i<10; i++)
					enemigoArreglo[i]->Actualizar();
				MoverEnemigo();
				SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
				keys = SDL_GetKeyState(NULL);
				if (keys[SDLK_RIGHT])
				{
					if (!EsLimitePantalla(nave, BORDE_DERECHO))
					nave->MoverX(1);

				}
				if (keys[SDLK_LEFT])
				{
					if (!EsLimitePantalla(nave, BORDE_IZQUIERDO))
					nave->MoverX(-1);
				}
				if (keys[SDLK_UP])
				{
					if (!EsLimitePantalla(nave, BORDE_SUPERIOR))
						nave->MoverY(-1);
				}
				if (keys[SDLK_DOWN])
				{
					if (!EsLimitePantalla(nave, BORDE_INFERIOR))
						nave->MoverY(1);
				}

			
				nave->Pintar();
				
				for (int i = 0; i < 10;i++)
				enemigoArreglo[i]->Pintar();
				if (keys[SDLK_SPACE])
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
			SDL_Flip(screen);  //guarda en memoria buffer

		}
		return true;
}
	bool CGame::EsLimitePantalla(Nave * objeto, int bandera)
	{
		if (bandera & BORDE_IZQUIERDO)
			if (objeto->ObtenerX() <= 0)
				return true;
		if (bandera & BORDE_SUPERIOR)
			if (objeto->ObtenerY() <= 0)
				return true;
		if (bandera & BORDE_DERECHO)
			if (objeto->ObtenerX() >= WIDTH_SCREEN - objeto->ObtenerW())
				return true;
		if (bandera & BORDE_INFERIOR)
			if (objeto->ObtenerY() >= HEIGHT_SCREEN - objeto->ObtenerH())
				return true;
		return false;
	}
	void CGame::MoverEnemigo()
	{
		
			for (int i= 0; i < 10; i++)
			{
				//paso 0
				if (enemigoArreglo[i]->ObtenerPasoActual() == 0)
					if (!EsLimitePantalla(enemigoArreglo[i], BORDE_DERECHO))
						enemigoArreglo[i]->MoverX(1);//DERECHA
					else{
						enemigoArreglo[i]->IncrementarPasoActual();
						enemigoArreglo[i]->IncrementarPasoActual();
					}
					// paso 1
					//if (enemigo->ObtenerPasoActual()==1)
					//   if (!!EsLimitePantalla(enemigo, BORDE_INFERIOR)
					//ENEMIGO->mIVER(1);ABAJO
					// paso 2
					if (enemigoArreglo[i]->ObtenerPasoActual() == 2)
						if (!EsLimitePantalla(enemigoArreglo[i], BORDE_IZQUIERDO))
							enemigoArreglo[i]->MoverX(-1); //IZQUIERDA
						else
						{
							enemigoArreglo[i]->IncrementarPasoActual();
							enemigoArreglo[i]->IncrementarPasoActual();
						}
					// if (enemigo->ObtenerPasoActual() == 3)
					// if (!EsLimitePantalla(enemigo, BORDE_INFERIOR))
					// ENEMIGO->MOVER(1); //ABAJO
			}
	}
