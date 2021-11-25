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

	//funcoes
	bool checkIntersect(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);

	const sf::Vector2f& getPosition() const;

	const sf::FloatRect getGlobalBounds() const;

	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

};

#endif