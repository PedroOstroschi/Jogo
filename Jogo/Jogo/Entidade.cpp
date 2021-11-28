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



/*Fun��es de Componente*/
void Entidade::createHitboxComponent(sf::Sprite& sprite,
	const float offset_x, const float offset_y,
	float width, float height)
{
	this->componenteHitbox = new ComponenteHitbox(sprite, offset_x, offset_y, width, height);
}

/*Fun��es*/
const sf::Vector2f& Entidade::getPosition() const
{
	if (this->componenteHitbox)
		return this->componenteHitbox->getPosition();

	return this->sprite.getPosition();
}

const sf::FloatRect Entidade::getGlobalBounds() const
{
	if (this->componenteHitbox)
		return this->componenteHitbox->getGlobalBounds();

	return this->sprite.getGlobalBounds();
}

void Entidade::setPosition(const float x, const float y)
{
	if (this->componenteHitbox)
		this->componenteHitbox->setPosition(x, y);
	else
		this->sprite.setPosition(x, y);
}

void Entidade::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entidade::renderiza(sf::RenderTarget& alvo)
{
	alvo.draw(this->sprite);

	if (this->componenteHitbox)
		this->componenteHitbox->render(alvo);
}