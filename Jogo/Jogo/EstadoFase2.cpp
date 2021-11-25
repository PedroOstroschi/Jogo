#include "stdafx.h"
#include "EstadoFase2.h"

/*Construtora e Destrutora*/
EstadoFase2::EstadoFase2(DataEstado* data_estado)
	:EstadoFase(data_estado)//, cooperativo)
{

}

EstadoFase2::~EstadoFase2()
{

}

void EstadoFase2::terminou()
{
	/*salva a pontuacao em um arquivo*/

}
