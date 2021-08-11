#include "Estado.h"

/*Construtora e Destrutora*/
Estado::Estado(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados, bool cooperativo)
{
	this->janela = janela;
	this->teclasDisponiveis = teclasDisponiveis;
	this->sair = false;
	this->cooperativo = cooperativo;
	this->ganhou = false;
	this->pausado = false;
	this->pontuacao = 0;
	this->estados = estados;
}

Estado:: ~Estado()
{
}

/*Set's e Get's*/
const bool& Estado::getSair() const { return this->sair; }
const bool& Estado::getCoop() const { return this->cooperativo; }
const bool& Estado::getGanhou() const { return this->ganhou; }

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

/*Funções*/

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

void Estado::atualizaTecla(const float& td)
{
}

void Estado::atualizaPosicaoMouse()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->janela);
	this->mousePosView = this->janela->mapPixelToCoords(sf::Mouse::getPosition(*this->janela));
}

void Estado::iniFontes()
{
	if (!this->font.loadFromFile("Fonts/comic.ttf"))
	{
		throw("nao carregou fonte");
	}
}