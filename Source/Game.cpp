#include <stdio.h>
#include <stdlib.h>
#include "Game.h"

CGame::CGame(){
	estado;//ACT2:Mal, Aqui debes de darle a "estado" su valor inicial, para indicar en que estado iniciara. Si la dejas asi, sola, el juego nunca tendra estado inicial.
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
