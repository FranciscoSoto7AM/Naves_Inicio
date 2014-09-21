#include <stdio.h>
#include <stdlib.h>
#include "Game.h"

CGame::CGame(){
	///AC2 <-- Aqui debes de iniciar tu estado
}

// Con esta función eliminaremos todos los elementos en pantalla
void CGame::Finalize(){
}

bool CGame::Start()
{
	// Esta variable nos ayudara a controlar la salida del juego...
	int salirJuego = false;
          
	while (salirJuego == false){
            
		//Maquina de estados
		switch(estado){
		case Estado::ESTADO_INICIANDO: //INICIALIZAR
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
    }
	return true;
}
