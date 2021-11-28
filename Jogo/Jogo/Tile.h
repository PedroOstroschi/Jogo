#ifndef TILE_H
#define TILE_H

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<vector>

#include"SFML\System.hpp"
#include"SFML\Window.hpp"
#include"SFML\Graphics.hpp"

enum TileTypes {DEFAULT = 0, DANO, RAPIDO, LERDO};

class Tile
{
private:

protected:
	sf::RectangleShape shape;
	bool colisao;
	short tipo;

public:
	Tile();
	Tile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool colisao = false, short tipo = TileTypes::DEFAULT);
	virtual ~Tile();

	//functions
	const bool& getCollision() const;
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const bool intersects(const sf::FloatRect bounds) const;
	const std::string getAsString() const;

	void update();
	void render(sf::RenderTarget& alvo);
};

#endif