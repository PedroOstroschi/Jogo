#include "Entidade.h"

//Construtora/Destrutora

Entidade::Entidade()
{
	this->forma.setSize(sf::Vector2f(50.f, 50.f));
	this->forma.setFillColor(sf::Color::White);
	this->forma.setPosition(sf::Vector2f(400.f, 300.f));

}

Entidade::~Entidade()
{
}



void Entidade::renderiza(sf::RenderTarget& alvo)
{
	alvo.draw(this->forma);
	std::cout << this->forma.getPosition().x << this->forma.getPosition().y << "\n";

}



