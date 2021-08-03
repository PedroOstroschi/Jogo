#include "Estado.h"

//construtora/destrutora
Estado::Estado(sf::RenderWindow* janela)
{
	this->janela = janela;
	this->sair = false;
	this->cooperativo = false;
	this->ganhou = false;
}
Estado:: ~Estado(){}

//get`s
const bool& Estado::getSair() const{ return this->sair; }
const bool& Estado::getCoop() const{ return this->cooperativo; }
const bool& Estado::getGanhou() const{ return this->ganhou; }



//funcoes gerais
void Estado::fechaEStado()
{
}
void Estado::pausaEstado()
{
}
void Estado::despausaEStado()
{
}

void Estado::atualiza(const float& td)
{
	

}

void Estado::renderiza()
{
}


