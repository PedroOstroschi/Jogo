#include "Botao.h"

/*Construtora e Destrutora*/
Botao::Botao(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color corIdleT, sf::Color corHoverT, sf::Color corActiveT,
	sf::Color corIdle, sf::Color corHover, sf::Color corActive)
{
	this->statusBotao = BTN_IDLE;

	this->box.setPosition(sf::Vector2f(x, y));
	this->box.setSize(sf::Vector2f(width, height));
	this->box.setFillColor(corIdle);

	this->font = font;
	this->texto.setFont(*this->font);
	this->texto.setString(text);
	this->texto.setFillColor(corIdleT);
	this->texto.setCharacterSize(character_size);
	this->texto.setPosition(
		this->box.getPosition().x + (this->box.getGlobalBounds().width / 2.f) - this->texto.getGlobalBounds().width / 2.f,
		this->box.getPosition().y + (this->box.getGlobalBounds().height / 2.f) - this->texto.getGlobalBounds().height / 2.f
	);
	
	this->corIdleT = corIdleT;
	this->corHoverT = corHoverT;
	this->corActiveT = corActiveT;

	this->corIdle = corIdle;
	this->corHover = corHover;
	this->corActive = corActive;

}
Botao::~Botao()
{

}



/*Flags*/
const bool Botao::isPressed() const
{
	if (this->statusBotao == BTN_ACTIVE)
		return true;
	return false;
}

/*Funções*/
void Botao::update(const sf::Vector2f mousePos)
{
	/*updeita os booleanos para ver se o mouse ta em cima ou pressionando o botao*/
	
	//inicia o botao em idle
	this->statusBotao = BTN_IDLE;
	//hover
	if (this->box.getGlobalBounds().contains(mousePos))
	{
		this->statusBotao = BTN_HOVER;

		//active
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->statusBotao = BTN_ACTIVE;
		}
	}

	switch (this->statusBotao)
	{
		case BTN_IDLE:
			this->box.setFillColor(this->corIdle);
			this->texto.setFillColor(this->corIdleT);
			break;

		case BTN_HOVER:
			this->box.setFillColor(this->corHover);
			this->texto.setFillColor(this->corHoverT);
			break;

		case BTN_ACTIVE:
			this->box.setFillColor(this->corActive);
			this->texto.setFillColor(this->corActiveT);
			break;

		default:
			this->box.setFillColor(sf::Color::Red);
			this->texto.setFillColor(sf::Color::Blue);
			break;

	}
}

void Botao::render(sf::RenderTarget& alvo)
{
	alvo.draw(this->box);
	alvo.draw(this->texto);
}
