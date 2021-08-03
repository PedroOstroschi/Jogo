#include "EstadoJogo.h"

//construtora / destrutora
EstadoJogo::EstadoJogo(sf::RenderWindow* janela)
	:Estado(janela, estados, cooperativo)
{
	
}

EstadoJogo::~EstadoJogo()
{
}


//funcoes
void EstadoJogo::fechaEstado()
{
}

void EstadoJogo::atualiza(const float td)
{
	atualizaTeclas(td);
}

void EstadoJogo::renderiza()
{
}

void EstadoJogo::atualizaTeclas(const float td)
{
}
