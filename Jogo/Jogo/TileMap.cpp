#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = NULL;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();

	//std::cout << this->map.size() << "\n";
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	this->textureFile = texture_file;

	this->map.resize(this->maxSize.x, std::vector< std::vector<Tile*> >());

	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());
			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}

	if(!this->tileSheet.loadFromFile(texture_file))
		std::cout << "ERRO::TILEMAP::NAO CARREGOU TEXTURA::FILENAME::" << texture_file << "\n";

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 30));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);
}

TileMap::~TileMap()
{
	this->clear();
}

//accessors
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

//functions
void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect, const bool colisao, const short tipo)
{
	/*pega o x, y e z da posicao do mouse no grid e adiciona uma tile naquele bloco se a matriz permitir*/

	if (x < this->maxSize.x && x >= 0 && 
	    y < this->maxSize.y && y >= 0 && 
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == NULL)
		{
			/*permitido adicionar tile*/
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, colisao, tipo);
			std::cout << "DEBUG: colocou tile" << "\n";
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	/*pega o x, y e z da posicao do mouse no grid e remove uma tile naquele bloco se a matriz permitir*/

	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != nullptr)
		{
			/*permitido remover tile*/
			delete this->map[x][y][z];
			this->map[x][y][z] = NULL;

			std::cout << "DEBUG: removeu tile" << "\n";
		}
	}

}

void TileMap::saveToFile(const std::string file_name)
{
	/*salva o tilemap inteiro em um txt
	size x y
	gridSize
	layers
	texture_file

	gridPos x y layer
	texture rect x y
	colisao
	tipo
	*/
	std::ofstream out_file;
	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSize.x << " " << this->maxSize.y << "\n"
			<< this->gridSizeU << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";
	
		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				for (size_t z = 0; z < this->layers; z++)
				{
					if(this->map[x][y][z])
						out_file << x << " " << y << " " << z << " " << 
						this->map[x][y][z]->getAsString()
						<< " "; //nao pode salvar esse ultimo espaco
				}
			}
		}
	}
	else
	{
		std::cout << "ERRO::TILEMAP::NAO_SALVOU_A_FILE::FILENAME::" << file_name << "\n";
	}

	out_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	/*salva o tilemap inteiro em um txt
	
	BASICO
	size x y
	gridSize
	layers
	texture_file

	ADV
	gridPos x y
	texture rect x y
	colisao
	tipo
	*/

	std::ifstream in_file;
	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;
		unsigned layers = 0;
		std::string texture_file = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool colisao = false;
		short tipo = 0;

		//basico
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSize.x, std::vector< std::vector<Tile*> >());
		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				this->map[x].resize(this->maxSize.y, std::vector<Tile*>());
				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, NULL);
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
			std::cout << "ERRO::TILEMAP::NAO CARREGOU TEXTURA::FILENAME::" << texture_file << "\n";

		//load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> colisao >> tipo)
		{
			this->map[x][y][z] = new Tile(
				x, y,
				this->gridSizeF, 
				this->tileSheet,
				sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU),
				colisao,
				tipo
			);
		}
	}
	else
	{
		std::cout << "ERRO::TILEMAP::NAO_CARREGOU_A_FILE::FILENAME::" << file_name << "\n";
	}

	in_file.close();
}

void TileMap::updateCollision(Entidade* entity)
{

}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& alvo, Entidade* entity)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if (z != NULL) 
				{
					z->render(alvo);
					if (z->getCollision())
					{
						this->collisionBox.setPosition(z->getPosition());
						alvo.draw(this->collisionBox);
					}
				}
			}
		}
	}
}