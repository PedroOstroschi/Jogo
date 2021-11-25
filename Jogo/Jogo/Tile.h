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

class Tile
{
private:

protected:
	sf::RectangleShape shape;

public:
	Tile();
	Tile(float x, float y, float gridSizeF);
	virtual ~Tile();

	//functions
	void update();
	void render(sf::RenderTarget& alvo);
};

#endif