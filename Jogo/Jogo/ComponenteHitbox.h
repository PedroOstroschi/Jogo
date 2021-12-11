#ifndef COMPONENTEHITBOX_H
#define COMPONENTEHITBOX_H

class ComponenteHitbox
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;


public:
	ComponenteHitbox(sf::Sprite& sprite, 
		float offset_x, float offset_y, 
		float width, float height);
	virtual ~ComponenteHitbox();

	//accessor
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	//modifiers
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);


	//funcoes
	bool intersects(const sf::FloatRect& frect);


	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	void update();
	void render(sf::RenderTarget& target);

};

#endif