#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			for (int z = 0; z < this->layers; z++)
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

TileMap::TileMap(float gridSize, int width, int height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<unsigned>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->textureFile = texture_file;

	this->fromX = 0;
	this->fromY = 0;
	this->toX = 0;
	this->toY = 0;
	this->layer = 0;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector<Tile*> >());

	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());
			for (int z = 0; z < this->layers; z++)
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
	this->collisionBox.setOutlineThickness(-1.f);
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
void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool colisao, const short tipo)
{
	/*pega o x, y e z da posicao do mouse no grid e adiciona uma tile naquele bloco se a matriz permitir*/

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
	    y < this->maxSizeWorldGrid.y && y >= 0 &&
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

void TileMap::removeTile(const int x, const int y, const int z)
{
	/*pega o x, y e z da posicao do mouse no grid e remove uma tile naquele bloco se a matriz permitir*/

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
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
		out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
			<< this->gridSizeI << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";
	
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
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
		sf::Vector2i size;
		int gridSize = 0;
		int layers = 0;
		std::string texture_file = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool colisao = false;
		short tipo = 0;

		//basico
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector< std::vector<Tile*> >());
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());
				for (int z = 0; z < this->layers; z++)
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
				sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
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

void TileMap::updateCollision(EntidadeDinamica* entity, const float& td)
{
	//JANELA
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x)
	{
		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	//TILES
	this->layer = 0;

	this->fromX = entity->getGridPosition(this->gridSizeI).x - 2;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorldGrid.x)
		this->fromX = this->maxSizeWorldGrid.x;

	this->toX = entity->getGridPosition(this->gridSizeI).x + 4;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorldGrid.x)
		this->toX = this->maxSizeWorldGrid.x;

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 2;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorldGrid.y)
		this->fromY = this->maxSizeWorldGrid.y;

	this->toY = entity->getGridPosition(this->gridSizeI).y + 4;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSizeWorldGrid.y)
		this->toY = this->maxSizeWorldGrid.y;

	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = fromY; y < this->toY; y++)
		{
			sf::FloatRect playerBounds = entity->getGlobalBounds();
			sf::FloatRect wallBounds = this->map[x][y][this->layer]->getGlobalBounds();
			sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(td);

			if (this->map[x][y][this->layer]->getCollision() && 
				this->map[x][y][this->layer]->intersects(nextPositionBounds))
			{
				//debug
				//std::cout << "COLISAO" << "\n";

				//bottom collision
				if (playerBounds.top < wallBounds.top &&
					playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height &&
					playerBounds.left < wallBounds.left + wallBounds.width &&
					playerBounds.left + playerBounds.width > wallBounds.left)
				{
					entity->stopVelocityY();
					entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
				}
				//top collision
				else if (playerBounds.top > wallBounds.top &&
					playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height &&
					playerBounds.left < wallBounds.left + wallBounds.width &&
					playerBounds.left + playerBounds.width > wallBounds.left)
				{
					entity->stopVelocityY();
					entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
				}
				//right collision
				if (playerBounds.left < wallBounds.left &&
					playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width &&
					playerBounds.top < wallBounds.top + wallBounds.height &&
					playerBounds.top + playerBounds.height > wallBounds.top)
				{
					entity->stopVelocityX();
					entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
				}
				//left collision
				if (playerBounds.left > wallBounds.left &&
					playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width &&
					playerBounds.top < wallBounds.top + wallBounds.height &&
					playerBounds.top + playerBounds.height > wallBounds.top)
				{
					entity->stopVelocityX();
					entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
				}

			}
		}
	}
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& alvo, Entidade* entity)
{
	if (entity)
	{
		this->layer = 0;

		this->fromX = (entity->getGridPosition(this->gridSizeI).x) - 5;
		if (this->fromX < 0)
			this->fromX = 0;
		else if (this->fromX > this->maxSizeWorldGrid.x)
			this->fromX = this->maxSizeWorldGrid.x;

		this->toX = (entity->getGridPosition(this->gridSizeI).x) + 8;
		if (this->toX < 0)
			this->toX = 0;
		else if (this->toX > this->maxSizeWorldGrid.x)
			this->toX = this->maxSizeWorldGrid.x;

		this->fromY = (entity->getGridPosition(this->gridSizeI).y) - 5;
		if (this->fromY < 0)
			this->fromY = 0;
		else if (this->fromY > this->maxSizeWorldGrid.y)
			this->fromY = this->maxSizeWorldGrid.y;

		this->toY = (entity->getGridPosition(this->gridSizeI).y) + 8;
		if (this->toY < 0)
			this->toY = 0;
		else if (this->toY > this->maxSizeWorldGrid.y)
			this->toY = this->maxSizeWorldGrid.y;

		for (int x = this->fromX; x < this->toX; x++)
		{
			for (int y = this->fromY; y < this->toY; y++)
			{
				this->map[x][y][this->layer]->render(alvo);
				if (this->map[x][y][this->layer]->getCollision())
				{
					this->collisionBox.setPosition(this->map[x][y][this->layer]->getPosition());
					alvo.draw(this->collisionBox);
				}
			}
		}
	}
	else
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
}
