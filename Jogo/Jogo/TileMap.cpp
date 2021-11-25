#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;

	this->map.resize(this->maxSize.x);
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		this->map.push_back(std::vector< std::vector<Tile*> >());

		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y);
			this->map[x].push_back(std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers);
				this->map[x][y].push_back(nullptr);
			}
		}
	}
}

TileMap::~TileMap()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
		}
	}
}

//functions
void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z)
{
	/*pega o x e y da posicao do mouse no grid e adiciona uma tile naquele bloco se a matriz permitir*/

	if (x < this->maxSize.x && x >= 0 && 
	    y < this->maxSize.y && y >= 0 && 
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == nullptr)
		{
			/*permitido adicionar tile*/
			this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF);

			std::cout << "DEBUG: colocou tile" << "\n";
		}
	}
}

void TileMap::removeTile()
{

}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget & alvo)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if (z != nullptr)
					z->render(alvo);
			}
		}
	}
}