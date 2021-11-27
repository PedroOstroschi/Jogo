#include "stdafx.h"
#include "Estado.h"

/*Construtora e Destrutora*/
Estado::Estado(DataEstado* data_estado)
{
	this->dataEstado = data_estado;
	this->janela = data_estado->janela;
	this->teclasDisponiveis = data_estado->teclasDisponiveis;
	this->sair = false;
	this->cooperativo = data_estado->cooperativo;
	this->ganhou = false;
	this->pausado = false;
	this->pontuacao = 0;
	this->estados = data_estado->estados;
	this->keytime = 0.f;
	this->keytimemax = 30.f;
	this->gridSize = data_estado->gridSize;
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

const bool& Estado::getKeytime()
{
	if (this->keytime >= keytimemax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
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

void Estado::atualizaPosicaoMouse(sf::View* view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->janela);

	if(view)
		this->janela->setView(*view);

	this->mousePosView = this->janela->mapPixelToCoords(sf::Mouse::getPosition(*this->janela));
	this->mousePosGrid = sf::Vector2u
	(
		static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->gridSize),
		static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->gridSize)
	);

	this->janela->setView(this->janela->getDefaultView());
}

void Estado::updateKeyTime(const float& td)
{
	if (this->keytime < this->keytimemax)
		this->keytime += 100.f * td;
}

void Estado::iniFontes()
{
	if (!this->font.loadFromFile("Fonts/comic.ttf"))
	{
		throw("nao carregou fonte");
	}
}