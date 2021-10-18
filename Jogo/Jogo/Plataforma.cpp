#include "Plataforma.h"

Plataforma::Plataforma(sf::Vector2f posicao, sf::Vector2f desCorpo, sf::Vector2f tamanhoCorpo, bool transparente)
{
	this->corpo.setFillColor(sf::Color::Red); /*Trocar por sprite*/
	this->corpo.setSize(tamanhoCorpo);
	this->corpo.setPosition(desCorpo);
}

Plataforma::~Plataforma()
{
}
