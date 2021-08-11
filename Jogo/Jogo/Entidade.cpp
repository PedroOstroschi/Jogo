#include "Entidade.h"

void Entidade::initVariaveis()
{

}

/*Construtora e Destrutora*/
Entidade::Entidade()
{
	this->initVariaveis();
}

Entidade::~Entidade()
{

}

/*Fun��es de Componente*/
void Entidade::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

/*Fun��es*/

void Entidade::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Entidade::renderiza(sf::RenderWindow* alvo)
{
	alvo->draw(this->sprite);
}