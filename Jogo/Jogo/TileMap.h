#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Entidade.h"

class Tile;
class Entidade;

class TileMap
{
private:
	void clear();

	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;

	sf::Vector2u maxSize;
	std::vector< std::vector< std::vector< Tile* > > > map;
	std::string textureFile;
	sf::Texture tileSheet;

	sf::RectangleShape collisionBox;

public:
	TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
	virtual ~TileMap();

	//accessors
	const sf::Texture* getTileSheet() const;


	//functions
	void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool colisao, const short tipo);
	void removeTile(const unsigned x, const unsigned y, const unsigned z);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void updateCollision(Entidade* entity);

	void update();
	void render(sf::RenderTarget& alvo, Entidade* entity = NULL);


};

#endif