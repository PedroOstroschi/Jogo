#include"SFML/Graphics.hpp"

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


public:

	/*Construtora e Destrutora*/
	ComponenteMovimento(sf::Sprite& sprite, float velocidadeMaxima, float aceleracao, float desaceleracao);
	virtual ~ComponenteMovimento();

	/*Accessors*/
	const sf::Vector2f& getVelocity() const;

	/*Funcoes*/
	void move(const float dir_x, const float dir_y, const float& td);
	void update(const float& dt);
};

