#include "stdafx.h"
#include "EntidadeDinamica.h"

void EntidadeDinamica::initVariaveis()
{
	this->componenteMovimento = NULL;
	this->componenteAnimacao = NULL;
}

/*Construtora e Destrutora*/
EntidadeDinamica::EntidadeDinamica() :
	Entidade()
{
	this->initVariaveis();
}

EntidadeDinamica::~EntidadeDinamica()
{
	delete this->componenteMovimento;
	delete this->componenteAnimacao;
}

/*Funcoes Componentes*/
void EntidadeDinamica::createMovementComponent(const float velocidadeMaxima, const float velocidadeMaximaY, const float aceleracao, const float desaceleracao)
{
	this->componenteMovimento = new ComponenteMovimento(this->sprite, velocidadeMaxima, velocidadeMaximaY, aceleracao, desaceleracao);
}

void EntidadeDinamica::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->componenteAnimacao = new ComponenteAnimacao(this->sprite, texture_sheet);
}


//


//
const sf::Vector2f EntidadeDinamica::getCenter() const
{
	if (this->componenteHitbox)
		return
		this->componenteHitbox->getPosition() +
		sf::Vector2f
		(
			this->componenteHitbox->getGlobalBounds().width / 2.f,
			this->componenteHitbox->getGlobalBounds().height / 2.f
		);

	return
		this->sprite.getPosition() +
		sf::Vector2f
		(
			this->sprite.getGlobalBounds().width / 2.f,
			this->sprite.getGlobalBounds().height / 2.f
		);
}

const sf::Vector2f EntidadeDinamica::getSpriteCenter() const
{
	return this->sprite.getPosition() +
		sf::Vector2f
		(
			this->sprite.getGlobalBounds().width / 2.f,
			this->sprite.getGlobalBounds().height / 2.f
		);;
}

const sf::Vector2f& EntidadeDinamica::getSpritePosition() const
{
	return this->sprite.getPosition();
}


/*Funções*/
void EntidadeDinamica::move(const float dir_x, const float dir_y, const float& td)
{
	if (this->componenteMovimento)
		this->componenteMovimento->move(dir_x, dir_y, td);	//seta velocidade
}

void EntidadeDinamica::stopVelocity()
{
	if (this->componenteMovimento)
		this->componenteMovimento->stopVelocity();
}

void EntidadeDinamica::stopVelocityX()
{
	if (this->componenteMovimento)
		this->componenteMovimento->stopVelocityX();
}

void EntidadeDinamica::stopVelocityY()
{
	if (this->componenteMovimento)
		this->componenteMovimento->stopVelocityY();
}

const sf::FloatRect& EntidadeDinamica::getNextPositionBounds(const float& td) const
{
	if (this->componenteHitbox && this->componenteMovimento)
		return this->componenteHitbox->getNextPosition(this->componenteMovimento->getVelocity() * td);
}

void EntidadeDinamica::atualiza(const float & td)
{

}