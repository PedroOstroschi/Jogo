#include "stdafx.h"
#include "Inimigo.h"

//Initializer functions
void Inimigo::initVariables()
{
	this->gainExp = 10;
	this->damageTimerMax = 1000;
	this->despawnTimerMax = 1000;
}

void Inimigo::initAnimations()
{

}

//Constructors / Destructors
Inimigo::Inimigo(/*EnemySpawnerTile& enemy_spawner_tile*/)
//	: enemySpawnerTile(enemy_spawner_tile)
{
	this->initVariables();
	this->initAnimations();
}

Inimigo::~Inimigo()
{

}

const unsigned& Inimigo::getGainExp() const
{
	return this->gainExp;
}

//EnemySpawnerTile& Inimigo::getEnemySpawnerTile()
//{
//	return this->enemySpawnerTile;
//}

const bool Inimigo::getDamageTimerDone() const
{
	return this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax;
}

const bool Inimigo::getDespawnTimerDone() const
{
	return this->despawnTimer.getElapsedTime().asMilliseconds() >= this->despawnTimerMax;
}

void Inimigo::resetDamageTimer()
{
	this->damageTimer.restart();
}

void Inimigo::generateAttributes(const unsigned level)
{
	this->gainExp = level * (rand() % 5 + 1);
}

void Inimigo::loseHP(const int hp)
{
	if (this->componenteAtributos)
	{
		this->componenteAtributos->loseHP(hp);
	}
}

const bool Inimigo::isDead() const
{
	if (this->componenteAtributos)
	{
		return this->componenteAtributos->isDead();
	}

	return false;
}

const ComponenteAtributos* Inimigo::getAttributeComp() const
{
	if (this->componenteAtributos)
		return this->componenteAtributos;
	else
	{
		std::cout << "ERROR::ENEMY::ATTRIBUTECOMPONENT IS NOT INITIALIZED" << "\n";
		return nullptr;
	}
}

void Inimigo::update(const float& dt, sf::Vector2f& mouse_pos_view, const sf::View& view)
{
	if (vectorDistance(this->getPosition(), view.getCenter()) < 1500.f)
		this->despawnTimer.restart();
}