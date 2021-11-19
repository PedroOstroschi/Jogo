#include "ComponenteHitbox.h"

ComponenteHitbox::ComponenteHitbox(sf::Sprite& sprite,
	float offset_x, float offset_y,
	float width, float height)
	: sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	this->nextPosition.left = 0.f;
	this->nextPosition.top = 0.f;
	this->nextPosition.width = width;
	this->nextPosition.height = height;

	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);

}

ComponenteHitbox::~ComponenteHitbox()
{

}

bool ComponenteHitbox::checkIntersect(const sf::FloatRect& frect)
{
		return this->hitbox.getGlobalBounds().intersects(frect);
}

void ComponenteHitbox::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void ComponenteHitbox::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}

//Accessors
const sf::Vector2f& ComponenteHitbox::getPosition() const
{
	return this->hitbox.getPosition();
}

const sf::FloatRect ComponenteHitbox::getGlobalBounds() const
{
	return this->hitbox.getGlobalBounds();
}

const sf::FloatRect& ComponenteHitbox::getNextPosition(const sf::Vector2f& velocity)
{
	this->nextPosition.left = this->hitbox.getPosition().x + velocity.x;
	this->nextPosition.top = this->hitbox.getPosition().y + velocity.y;

	return this->nextPosition;
}
