#include <stdio.h>
#include <stdlib.h>
#include "Game.h"
#include "Config.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Sprite.h"





CGame::CGame(){
	estado = ESTADO_INICIANDO;
	//ACT2:Mal, Aqui debes de darle a "estado" su valor inicial, para indicar en que estado iniciara. Si la dejas asi, sola, el juego nunca tendra estado inicial.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("no se pudo iniciar SDL: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	screen = SDL_SetVideoMode(WIDTH_SCREEN, HEIGHT_SCREEN, 24, SDL_HWSURFACE);
	if (screen == NULL)
	{
		printf("no se puede inicializar el modo grafico: \n", SDL_GetError());
		exit(1);
		atexit(SDL_Quit);
	}
	SDL_WM_SetCaption("Mi Primer Juego", NULL);
	

	nave = new Sprite(screen);
	nave->CargaImagen("../Data/minave.bmp");
}

// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
	delete(nave);
	SDL_FreeSurface(screen);
	SDL_Quit();
}

void CGame::Iniciando()
{
	if (screen == NULL){
		printf("Error %s", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_WM_SetCaption("Mi primer Juego", NULL);
	atexit(SDL_Quit);
	nave = new Sprite(screen);
	nave->CargaImagen("../Dta/MiNave.bmp");
	//delete nave;	

}

bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;
          
	while (salirJuego == false){
            
		//Maquina de estados
		switch(estado){
		case Estado::ESTADO_INICIANDO: //inicializando
  		    Iniciando(); 
			estado = ESTADO_MENU;
			{
				/*nave=SDL_LoadBMP("../DATA/nave.bmp");			
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

				SDL_BlitSurface(nave, &fuente, screen, &destino);*/
			}
			break;
		case Estado::ESTADO_MENU:	   //MENU	
			//nave->PintarModulo(0, 0, 0, 64, 64);
			nave->PintarModulo(0, 0, 0);
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
