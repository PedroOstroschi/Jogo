#ifndef GUI_H
#define GUI_H
#include"Estado.h"
#include<vector>

enum status_botao { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

namespace gui
{

	class Botao
	{
	private:
		/*Variaveis*/
		short unsigned statusBotao;
		short unsigned id;

		sf::RectangleShape box;
		sf::Font* font;
		sf::Text texto;

		sf::Color corIdleT;
		sf::Color corHoverT;
		sf::Color corActiveT;

		sf::Color corIdle;
		sf::Color corHover;
		sf::Color corActive;

		sf::Color outlinecorIdle;
		sf::Color outlinecorHover;
		sf::Color outlinecorActive;

	public:
		/*Construtora e destrutora*/
		Botao(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color corIdleT, sf::Color corHoverT, sf::Color corActiveT,
			sf::Color corIdle, sf::Color corHover, sf::Color corActive,
			sf::Color outlinecorIdle = sf::Color::Transparent, sf::Color outlinecorHover = sf::Color::Transparent, sf::Color outlinecorActive = sf::Color::Transparent,
			short unsigned id = 0);
		~Botao();

		/*Accessors*/
		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		/*Modifiers*/
		void setText(const std::string text);
		void setId(const short unsigned id);

		/*Funções*/
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& alvo);

	};

	class DropDownList
	{
	private:
		float keytime;
		float keytimeMax;

		sf::Font& font;
		gui::Botao* activeElement;
		std::vector<gui::Botao*> list;
		bool showList;

	public:
		/*Construtora e destrutora*/
		DropDownList(float x, float y, float width, float height, 
			sf::Font& font, std::string list[], 
			unsigned nrOfElements, unsigned default_index = 0);
		~DropDownList();

		//accessors
		const unsigned short& getActiveElementdId() const;

		/*Funções*/
		const bool getKeytime();
		void updateKeytime(const float& td);
		void update(const sf::Vector2f& mousePos, const float& td);
		void render(sf::RenderTarget& alvo);
	};
}

#endif