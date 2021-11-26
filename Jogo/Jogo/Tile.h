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
	Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool colisao = false, short tipo = TileTypes::DEFAULT);
	virtual ~Tile();

	//functions
	const std::string getAsString() const;

	void update();
	void render(sf::RenderTarget& alvo);
};

#endif