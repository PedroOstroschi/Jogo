#include "Estado.h"

//construtora/destrutora
Estado::Estado(sf::RenderWindow* janela, std::stack<Estado*>* estados, bool cooperativo)
{
	this->janela = janela;
	this->sair = false;
	this->cooperativo = cooperativo;
	this->ganhou = false;
	this->pausado = false;
	this->pontuacao = 0;
	this->estados = estados;
}
Estado:: ~Estado(){}

//get`s
const bool& Estado::getSair() const{ return this->sair; }
const bool& Estado::getCoop() const{ return this->cooperativo; }
const bool& Estado::getGanhou() const{ return this->ganhou; }

const bool& Estado::getPausado() const
{
	return this->pausado;
}

void Estado::setPontuacao(const int pont)
{
	this->pontuacao = pont;
}

const int Estado::getPontuacao()
{
	return this->pontuacao;
}



//funcoes gerais
void Estado::fechaEstado()
{
	this->sair = true;
}
void Estado::pausaEstado()
{
	this->pausado = true;
}
void Estado::despausaEstado()
{
	this->pausado = false;
}

void Estado::atualiza(const float& td)
{
	this->atualizaTecla(td);
}

void Estado::renderiza()
{
}

void Estado::atualizaTecla(const float& td)
{
}


