#ifndef GUI_H
#define GUI_H
#include "stdafx.h"
#include"Estado.h"

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
		void update(const sf::Vector2i& mousePosWindow);
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
		void update(const sf::Vector2i& mousePosWindow, const float& td);
		void render(sf::RenderTarget& alvo);
	};

	class TextureSelector
	{
	private:
		float keytime;
		const float keytimeMax;
		float gridSize;
		bool active;
		bool hidden;
		Botao* minimizar;

		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;

	public:
		TextureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture* texture_sheet, sf::Font& font, std::string text);
		~TextureSelector();

		//accessors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;

		//functions
		const bool getKeyTime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& td);
		void render(sf::RenderTarget& alvo);

	};
}

#endif