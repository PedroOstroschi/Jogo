#include "stdafx.h"
#include "Entidade.h"

void Entidade::initVariaveis()
{
	//vai dar conflito com o initvariaveis da entidade dinamica?
	//prolly not
	this->componenteHitbox = NULL;
}

/*Construtora e Destrutora*/
Entidade::Entidade()
{
	this->initVariaveis();
}

Entidade::~Entidade()
{
	delete this->componenteHitbox;
}

const sf::Vector2f& Entidade::getPosition() const
{
	return this->sprite.getPosition();
}

/*Funções de Componente*/
void Entidade::createHitboxComponent(sf::Sprite& sprite,
	const float offset_x, const float offset_y,
	float width, float height)
{
	this->componenteHitbox = new ComponenteHitbox(sprite, offset_x, offset_y, width, height);
}

/*Funções*/
void Entidade::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entidade::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Entidade::renderiza(sf::RenderTarget& alvo)
{
	alvo.draw(this->sprite);

	if (this->componenteHitbox)
		this->componenteHitbox->render(alvo);
}