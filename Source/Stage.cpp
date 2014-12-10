
#include"Game.h"

void CGame::InicializandoStage(){
	nivel[0].FondoNivel = 0;
	nivel[0].BalasMaximas = 3;
	nivel[0].NumeroEnemigoAEliminar = 10;
	nivel[0].NumeroEnemigosVisibles = 2;
	nivel[0].VelocidadBalasEnemigo = 5;
	nivel[0].VelocidadBalasPropias = 10;
	nivel[0].VelocidadNaveEnemigo = 10;
	nivel[0].VelocidadNavePropia = 5;
	nivel[0].VidaEnemigo = 1;

	nivel[1].FondoNivel = 1;
	nivel[1].BalasMaximas = 6;
	nivel[1].NumeroEnemigoAEliminar = 120;
	nivel[1].NumeroEnemigosVisibles = 4;
	nivel[1].VelocidadBalasEnemigo = 10;
	nivel[1].VelocidadBalasPropias = 20;
	nivel[1].VelocidadNaveEnemigo = 20;
	nivel[1].VelocidadNavePropia = 10;
	nivel[1].VidaEnemigo = 2;

}

