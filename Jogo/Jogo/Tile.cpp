#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->colisao = false;
	this->tipo = 0;
}

Tile::Tile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
	bool colisao, short tipo)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::White);
	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_rect);

	this->colisao = colisao;
	this->tipo = tipo;
}

Tile::~Tile()
{

}


const bool& Tile::getCollision() const
{
	return this->colisao;
}

const sf::Vector2f& Tile::getPosition() const
{
	return this->shape.getPosition();
}

//funcitons
const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->colisao << " " << this->tipo;

	return ss.str();
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds);
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& alvo)
{
	alvo.draw(this->shape);
}

