#include "stdafx.h"
#include "Jogador.h"

/*Funcoes Inicializadoras*/
void Jogador::iniVariaveis()
{
	this->attacking = false;
}

void Jogador::iniComponentes()
{

}

/*Construtora e Destrutora*/
Jogador::Jogador(float x, float y, sf::Texture& texture_sheet)
{

	this->iniVariaveis();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 165.f, 140.f, 81.f, 120.f);
	this->createMovementComponent(500.f, 20.f, 250.f, 100.f);
	this->createAnimationComponent(texture_sheet);

	//"key",					animation_timer, start_frame_x, start_frame_y, frames_x, frames_y, width, height)
	this->componenteAnimacao->addAnimation("IDLE", 10.f, 0, 0, 9, 0, 405, 405);
	this->componenteAnimacao->addAnimation("WALK", 5.f, 0, 4, 5, 4, 405, 405);
	this->componenteAnimacao->addAnimation("JUMP", 10.f, 8, 3, 1, 3, 405, 405);
	this->componenteAnimacao->addAnimation("FALL", 10.f, 8, 2, 1, 2, 405, 405);
	this->componenteAnimacao->addAnimation("ATK1", 7.f, 0, 2, 3, 2, 405, 405);
	this->componenteAnimacao->addAnimation("ATK2", 10.f, 4, 2, 3, 2, 405, 405);
	this->componenteAnimacao->addAnimation("ATK3", 10.f, 0, 3, 4, 3, 405, 405);
	this->componenteAnimacao->addAnimation("DEAD", 10.f, 0, 1, 8, 1, 405, 405);
	this->componenteAnimacao->addAnimation("HIT", 10.f, 5, 3, 2, 3, 405, 405);
}

Jogador::~Jogador()
{
	
}

void Jogador::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}
}

void Jogador::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		//anima e checa o final da animacao
		if (this->componenteAnimacao->play("ATK1", dt, true))
			this->attacking = false;
	}

	if (this->componenteMovimento->getState(IDLE))
	{
		this->componenteAnimacao->play("IDLE", dt);
	}

	else if (this->componenteMovimento->getState(MOVE_LEFT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(405.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}

		this->componenteAnimacao->play("WALK", dt, this->componenteMovimento->getVelocity().x, this->componenteMovimento->getMaxVelocity());
	}

	else if (this->componenteMovimento->getState(MOVE_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}

		this->componenteAnimacao->play("WALK", dt, this->componenteMovimento->getVelocity().x, this->componenteMovimento->getMaxVelocity());
	}

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		this->componenteAnimacao->play("ATK1", dt);

	else if (this->componenteMovimento->getState(JUMP))
	{
		this->componenteAnimacao->play("JUMP", dt);
	}
	else if (this->componenteMovimento->getState(FALL))
	{
		this->componenteAnimacao->play("FALL", dt);
	}*/
}

void Jogador::atualiza(const float& dt)
{
	this->componenteMovimento->update(dt);

	this->updateAttack();

	this->updateAnimation(dt);
	
	this->componenteHitbox->update();
}

void Jogador::render(sf::RenderTarget& alvo)
{
	//alvo.draw(this->sprite);

	//this->componenteHitbox->render(alvo);
}
