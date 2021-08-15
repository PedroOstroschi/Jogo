#include "MenuPause.h"

/*Construtora e Destrutora*/
MenuPause::MenuPause(sf::RenderWindow& janela)
{
	//inicia background
	this->background.setSize(
		sf::Vector2f(
			static_cast<float>(janela.getSize().x), 
			static_cast<float>(janela.getSize().y)
		)
	);

	this->background.setFillColor(sf::Color::Red);

	//inicia container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(janela.getSize().x) / 4.f,
			static_cast<float>(janela.getSize().y)
		)
	);
	this->container.setFillColor(sf::Color::Blue);
	this->container.setPosition(
		static_cast<float>(janela.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		0.f
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


/*Funções*/
void MenuPause::atualiza()
{

}

void MenuPause::renderiza(sf::RenderTarget* alvo)
{
	alvo->draw(background);
	alvo->draw(container);

	for (auto &i : this->botoes)
	{
		i.second->render(alvo);
	}
}