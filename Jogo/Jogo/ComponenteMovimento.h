#include"SFML/Graphics.hpp"
#include "ComponenteHitbox.h"

enum movement_states { IDLE = 0, MOVE_LEFT, MOVE_RIGHT, JUMP, FALL };

class ComponenteMovimento
{
private:
	sf::Sprite& sprite;

	float velocidadeMaxima;
	float velocidadeMaximaY;
	float aceleracao;
	float desaceleracao;
	float gravidade;

	sf::Vector2f velocidade;

	/*Inicializadores*/
	//nao precisa lol

public:

	/*Construtora e Destrutora*/
	ComponenteMovimento(sf::Sprite& sprite, float velocidadeMaxima, float velocidadeMaximaY, float aceleracao, float desaceleracao);
	virtual ~ComponenteMovimento();

	/*Accessors*/
	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;

	/*Funcoes*/
	const bool getState(const short unsigned state) const;

	void move(const float dir_x, const float dir_y, const float& td);
	void update(const float& dt);
};

