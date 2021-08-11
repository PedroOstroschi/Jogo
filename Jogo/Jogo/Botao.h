#include"Estado.h"

enum status_botao { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Botao
{
private:
	/*Variaveis*/
	short unsigned statusBotao;

	sf::RectangleShape box;
	sf::Font* font;
	sf::Text texto;

	sf::Color corIdleT;
	sf::Color corHoverT;
	sf::Color corActiveT;

	sf::Color corIdle;
	sf::Color corHover;
	sf::Color corActive;

public:
	/*Construtora e destrutora*/
	Botao(float x, float y, float width, float height, 
		sf::Font* font, std::string text, unsigned character_size,
		sf::Color corIdleT, sf::Color corHoverT, sf::Color corActiveT,
		sf::Color corIdle, sf::Color corHover, sf::Color corActive);
	~Botao();

	/*Flags*/
	const bool isPressed() const;

	/*Funções*/
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* alvo);

};
