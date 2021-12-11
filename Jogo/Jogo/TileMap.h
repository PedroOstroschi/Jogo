#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "Entidade.h"
#include "EntidadeDinamica.h"

class Tile;
class Entidade;
class EntidadeDinamica;

class TileMap
{
private:
	void clear();

	float gridSizeF;
	int gridSizeI;
	int layers;

	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	std::vector< std::vector< std::vector< Tile* > > > map;
	std::string textureFile;
	sf::Texture tileSheet;

	sf::RectangleShape collisionBox;

	//culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer = 0;

public:
	TileMap(float gridSize, int width, int height, std::string texture_file);
	virtual ~TileMap();

	//accessors
	const sf::Texture* getTileSheet() const;


	//functions
	void addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool colisao, const short tipo);
	void removeTile(const int x, const int y, const int z);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void updateCollision(EntidadeDinamica* entity, const float& td);

	void update();
	void render(sf::RenderTarget& alvo, Entidade* entity = NULL);


};

#endif