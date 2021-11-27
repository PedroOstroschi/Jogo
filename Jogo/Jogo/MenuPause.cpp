#include "stdafx.h"
#include "MenuPause.h"

/*inicializadoras*/
void MenuPause::iniBotoes()
{

}

void MenuPause::iniFontes()
{
	if (!this->font.loadFromFile("Fonts/comic.ttf"))
	{
		throw("nao carregou fonte");
	}
}

//inicia background
void MenuPause::iniPlanoDeFundo(sf::RenderWindow* janela)
{
	
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->janela->getSize().x),
			static_cast<float>(this->janela->getSize().y)
		)
	);

	this->background.setFillColor(sf::Color(20, 20, 20 ,100));

	//inicia container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(janela->getSize().x) / 4.f,
			static_cast<float>(janela->getSize().y) - 60.f
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		static_cast<float>(janela->getSize().x) / 2.f - this->container.getSize().x / 2.f,
		0
	);
}

/*Construtora e Destrutora*/
MenuPause::MenuPause(sf::RenderWindow* janela, sf::Font& font)
	:font(font)
{
	this->janela = janela;
	this->estados = estados;
	this->iniBotoes();
	this->iniFontes();
	this->iniPlanoDeFundo(janela);

	this->textoMenuPause.setFont(font);
	this->textoMenuPause.setFillColor(sf::Color::White);
	this->textoMenuPause.setCharacterSize(60);
	this->textoMenuPause.setString("PAUSADO");
	this->textoMenuPause.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->textoMenuPause.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 40.f
	);
}

MenuPause::~MenuPause()
{
	auto it = this->botoes.begin();
	for (it = this->botoes.begin(); it != this->botoes.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, gui::Botao*>& MenuPause::getButtons()
{
	return this->botoes;
}

/*Funções*/
const bool MenuPause::isButtonPressed(const std::string key) 
{
	return this->botoes[key]->isPressed();
}

void MenuPause::addButton(const std::string key, float y, const std::string text)
{
	float width = 250.f;
	float height = 50.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->botoes[key] = new gui::Botao(
		x, y, width, height,
		&this->font, text, 50,
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void MenuPause::atualiza(const sf::Vector2i& mousePosWindow)
{
	atualizaBotoes();
	atualizaPosicaoMouse();

	for (auto& i : this->botoes)
	{
		i.second->update(mousePosWindow);
	}

}

void MenuPause::renderiza(sf::RenderTarget& alvo)
{
	alvo.draw(this->background);
	alvo.draw(this->container);

	for (auto &i : this->botoes)
	{
		i.second->render(alvo);
	}

	alvo.draw(this->textoMenuPause);
}

void MenuPause::atualizaBotoes()
{
	/*atualiza todos os botoes desse estado e cuida das suas funcionalidades*/
	//main loop
	for (auto& it : this->botoes)
	{
		it.second->update(this->mousePosWindow);
	}
}

void MenuPause::atualizaPosicaoMouse()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->janela);
	this->mousePosView = this->janela->mapPixelToCoords(sf::Mouse::getPosition(*this->janela));
}
