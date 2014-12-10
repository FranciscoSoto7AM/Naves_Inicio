#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Config.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Sprite.h"


// maestro este es el bueno para el examen


CGame::CGame(){
	tiempoFrameInicial = 0;
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
	/*if (screen == NULL)
	{
		screen = SDL_SetVideoMode(640, 480, 24, SDL_SWSURFACE);
	}
	if (screen == NULL)
	{
		screen = SDL_SetVideoMode(640, 480, 24, SDL_SWSURFACE);
	}*/
	if (screen == NULL)
	{
		printf("Error %s ", SDL_GetError());
		exit(EXIT_FAILURE);

		
	}
	SDL_WM_SetCaption("Mi Primer video Juego", NULL);

		nave = new Nave(screen, "../Data/minave.bmp", (WIDTH_SCREEN / 2) , (HEIGHT_SCREEN - 80),MODULO_minave_NAVE);
		menu = new Objeto(screen, "../Data/FondoMenu.bmp", 0, 0,MODULO_FondoMenu_FONDO);
		textos = new Objeto(screen, "../Data/FondoTexto.bmp", 0, 0,-1);
		fondo = new Objeto(screen, "../Data/FondoJuego.bmp", 0, 0,MODULO_FondoMenu_FONDO);
		

		for (int i = 0; i < 10; i++)
		{
			enemigoArreglo[i] = new Nave(screen, "../Data/enemigo.bmp",i* 60,0,MODULO_enemigo_NAVE);
			enemigoArreglo[i]->GetNaveObjeto()->SetAutoMovimiento(false);
			enemigoArreglo[i]->GetNaveObjeto()->SetPasoLimite(4);
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
				InicializandoStage();
				estado = ESTADO_MENU;    //estado = ESTADO_MENU 
				break;
			case Estado::ESTADO_MENU:	   //MENU
				menu->Pintar();
				textos->Pintar(MODULO_FondoTexto_TITULO,160,50);
				textos->Pintar(MODULO_FondoMenu_NOMBRE,400, 410);
				Menu();
				
				
				

				//estado= ESTADO_JUGANDO
				break;

			case ESTADO_PRE_JUGANDO:
				NivelActual = 0;
				vida = 1;
				enemigosEliminados = 0;
				estado = ESTADO_JUGANDO;

				break;
			case Estado::ESTADO_JUGANDO: //JUGAR
				
				for (int i = 0; i < nivel[NivelActual].NumeroEnemigosVisibles; i++)
				{
					enemigoArreglo[i]->GetNaveObjeto()->Actualizar();
				}
				MoverEnemigo();
				fondo->Pintar();
				//SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
				keys = SDL_GetKeyState(NULL);
				if (keys[SDLK_RIGHT])
				{
					if (!EsLimitePantalla(nave->GetNaveObjeto(), BORDE_DERECHO))
						nave->MoverDerecha(nivel[NivelActual].VelocidadNavePropia);

				}
				if (keys[SDLK_LEFT])
				{
					if (!EsLimitePantalla(nave->GetNaveObjeto(), BORDE_IZQUIERDO))
						nave->MoverIzquierda(nivel[NivelActual].VelocidadNavePropia);
				}
				if (keys[SDLK_UP])
				{
					if (!EsLimitePantalla(nave->GetNaveObjeto(), BORDE_SUPERIOR))
						nave->MoverArriba(nivel[NivelActual].VelocidadNavePropia);
				}
				if (keys[SDLK_DOWN])
				{
					if (!EsLimitePantalla(nave->GetNaveObjeto(), BORDE_INFERIOR))
						nave->MoverAbajo(nivel[NivelActual].VelocidadNavePropia);
				}
				if (keys[SDLK_SPACE])
				{
					nave->Disparar(NAVE_PROPIA, nivel[NivelActual].BalasMaximas);
				}

				//////////////simulacion de coliciones
				if (keys[SDLK_x]){//bala enemigo a nuestra nave
					nave->simularColision(true);

				}

				if (keys[SDLK_c]){//nuestra bala a nave enemigo
					int enemigoAEliminar = rand() % nivel[NivelActual].NumeroEnemigosVisibles;
					enemigoArreglo[enemigoAEliminar]->simularColision(true);
				}


				if (keys[SDLK_v]){//nuestra nave a nave enemigo
				}
				///////////////////////////////////////////////
				//control de coliciones

				for (int i = 0; i<nivel[NivelActual].NumeroEnemigosVisibles; i++){
					if (enemigoArreglo[i]->estaColicionandoConBala(nave))
						vida--;
					if (nave->estaColicionandoConBala(enemigoArreglo[i])){
						enemigoArreglo[i]->setVisible(false);
						enemigosEliminados++;
						nave->simularColision(false);
						if (enemigosEliminados < nivel[NivelActual].NumeroEnemigoAEliminar){
							enemigoArreglo[i]->CrearNuevo();
						}
					}

				}

				///////////////////////////////////////
				if (vida <= 0)
					estado = ESTADO_TERMINANDO;
				if (enemigosEliminados >= nivel[NivelActual].NumeroEnemigoAEliminar){
					NivelActual++;

				}
			
				nave->Pintar(NAVE_PROPIA);
				
				for (int i = 0; i < nivel[NivelActual].NumeroEnemigosVisibles; i++)
				{
					enemigoArreglo[i]->Pintar(NAVE_ENEMIGO);
					enemigoArreglo[i]->AutoDispara(nivel[NivelActual].BalasMaximas);
				}

				if (keys[SDLK_ESCAPE])
				{
			
					
				}
				break;

			case Estado::ESTADO_TERMINANDO: //TERMINAR
				
				break;

			case Estado::ESTADO_FINALIZADO:  //FINALIZAR
				
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
	bool CGame::EsLimitePantalla(Objeto * objeto , int bandera)
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
		
		for (int i = 0; i < nivel[NivelActual].NumeroEnemigosVisibles; i++)
			{
				//// paso 0
				if (enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual() == 0)
					if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_DERECHO))
					{
					enemigoArreglo[i]->GetNaveObjeto()->MoverX(nivel[NivelActual].VelocidadNaveEnemigo);
					}
					else
					{
						enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();
					}
				//// paso 1
				if (enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual() == 1)
					if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_INFERIOR))
					{
					enemigoArreglo[i]->GetNaveObjeto()->MoverY(nivel[NivelActual].VelocidadNaveEnemigo);//ABAJO
					}
					else
					{

						enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();
					}

				//// paso 2
				if (enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual() == 2)
					if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_IZQUIERDO))
						enemigoArreglo[i]->GetNaveObjeto()->MoverX(-nivel[NivelActual].VelocidadNaveEnemigo);//IZQUIERDA

					else
					{

						enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();
					}
				//// paso 3
				if (enemigoArreglo[i]->GetNaveObjeto()->ObtenerPasoActual() == 3)
					if (!EsLimitePantalla(enemigoArreglo[i]->GetNaveObjeto(), BORDE_SUPERIOR))
					{
					enemigoArreglo[i]->GetNaveObjeto()->MoverY(-nivel[NivelActual].VelocidadNaveEnemigo);//ABAJO
					}
					else
					{

						enemigoArreglo[i]->GetNaveObjeto()->IncrementarPasoActual();
						}
					// if (enemigo->ObtenerPasoActual() == 3)
					// if (!EsLimitePantalla(enemigo, BORDE_INFERIOR))
					// ENEMIGO->MOVER(1); //ABAJO
			}
	}

	bool Objeto::EstaColicionando(Objeto * b)
	{
		return false;
	}

	void CGame::Menu()
	{
		for (int i = MODULO_FondoMenu_MENU_OPCION1, j=0; i <= MODULO_FondoMenu_MENU_OPCION2; i++, j++)
		{
			keys = SDL_GetKeyState(NULL);
			if (keys[SDLK_UP])
			{
				opcionSeleccionada = MODULO_FondoMenu_MENU_OPCION1;
				/* if (i == opcionSeleccionada)
				textos->Pintar(i + 2, 312, 250 + (j * 30));
				else
				textos->Pintar(i, 310, 250 + (j * 30));*/
			}

			if (keys[SDLK_DOWN])
			{
				opcionSeleccionada = MODULO_FondoMenu_MENU_OPCION2 ;
				/*if (i == opcionSeleccionada)
				textos->Pintar(i + 2, 308, 250 + (j * 30));
				else
				textos->Pintar(i, 310, 250 + (j * 30));*/

			}

			/*if (i == opcionSeleccionada)
			textos->Pintar(i + 2, 308, 250 + (j * 30));
			else
			textos->Pintar(i, 310, 250 + (j * 30));*/

			if (i == opcionSeleccionada)
				textos->Pintar(i + 2, 312, 250 + (j * 30));
			else
				textos->Pintar(i, 310, 250 + (j * 30));


			if (keys[SDLK_RETURN])
			{
				if (opcionSeleccionada == MODULO_FondoMenu_MENU_OPCION1)
				{
					estado = Estado::ESTADO_PRE_JUGANDO;
				}

				if (opcionSeleccionada == MODULO_FondoMenu_MENU_OPCION2)
				{
					estado = Estado::ESTADO_FINALIZADO;
				}
			}// sdlk_return
		}//for
	}//void
		