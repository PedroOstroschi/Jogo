#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, float gridSizeF)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(x, y);
}

Tile::~Tile()
{

}

//funcitons
void Tile::update()
{

}

void Tile::render(sf::RenderTarget& alvo)
{
	alvo.draw(this->shape);
}
