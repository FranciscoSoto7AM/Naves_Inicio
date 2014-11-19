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

		nave = new Nave(screen, "../Data/minave.bmp", (WIDTH_SCREEN / 2) , (HEIGHT_SCREEN - 80),MODULO_minave_NAVE);
		menu = new Nave(screen, "../Data/FondoMenu.bmp", 0, 0,MODULO_FondoMenu_FONDO);
		textos = new Nave(screen, "../Data/FondoTexto.bmp", 0, 0,-1);
		

		for (int i = 0; i < 10; i++)
		{
			enemigoArreglo[i] = new Nave(screen, "../Data/enemigo.bmp",i* 60,0,MODULO_enemigo_NAVE);
			enemigoArreglo[i]->SetAutoMovimiento(false);
			enemigoArreglo[i]->SetPasoLimite(4);
		}
		
		tick = 0;
		opcionSeleccionada = MODULO_FondoMenu_MENU_OPCION1;

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
				menu->Pintar();
				textos->Pintar(MODULO_FondoTexto_TITULO,160,50);
				textos->Pintar(MODULO_FondoMenu_NOMBRE,400, 410);
				Menu();
				
				
				

				//estado= ESTADO_JUGANDO
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
					nave->MoverX(5);

				}
				if (keys[SDLK_LEFT])
				{
					if (!EsLimitePantalla(nave, BORDE_IZQUIERDO))
					nave->MoverX(-5);
				}
				if (keys[SDLK_UP])
				{
					if (!EsLimitePantalla(nave, BORDE_SUPERIOR))
						nave->MoverY(-5);
				}
				if (keys[SDLK_DOWN])
				{
					if (!EsLimitePantalla(nave, BORDE_INFERIOR))
						nave->MoverY(5);
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

			//calculando FPS
			tiempoFrameFinal = SDL_GetTicks();
			while (tiempoFrameFinal < (tiempoFrameInicial + FPS_DELAY)){
				tiempoFrameFinal = SDL_GetTicks();
				SDL_Delay(1);
			}


			printf("Frames:%d Tiempo:%d Tiempo Promedio:%f Tiempo Por Frame:%d FPS:%f\n", tick, SDL_GetTicks(), (float)SDL_GetTicks() / (float)tick, tiempoFrameFinal - tiempoFrameInicial,1000.0f / (float) (tiempoFrameFinal-tiempoFrameInicial));
		    tiempoFrameInicial = tiempoFrameFinal; //Marcamos el inicio nuevamente
			tick++;
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
						enemigoArreglo[i]->MoverX(10);//DERECHA
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
							enemigoArreglo[i]->MoverX(-10); //IZQUIERDA
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

	void CGame::Menu()
	{
		for (int i = MODULO_FondoMenu_MENU_OPCION1, j=0; i <= MODULO_FondoMenu_MENU_OPCION2; i++, j++)
		{
			if (i == opcionSeleccionada)
				textos->Pintar(i+2, 220, 180 + (j * 80));
			else
			textos -> Pintar(i, 220, 180 + (j * 80));
		}
	}
