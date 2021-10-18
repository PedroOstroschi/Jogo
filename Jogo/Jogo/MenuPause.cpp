#include "MenuPause.h"

/*inicializadoras*/
void MenuPause::iniBotoes()
{
	this->botoes["DESPAUSAR"] = new Botao(802, 700, 150, 50,
		&this->font, "Despausar", 24,
		sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

	this->botoes["SALVAR"] = new Botao(970, 700, 150, 50,
		&this->font, "Salvar", 24,
		sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));


	this->botoes["SAIR"] = new Botao(970, 770, 150, 50,
		&this->font, "Sair", 24,
		sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
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
		sf::Vector2f(
			static_cast<float>(janela->getSize().x),
			static_cast<float>(janela->getSize().y)
		)
	);

	this->background.setFillColor(sf::Color::Red);

	//inicia container
	this->container.setSize(
		sf::Vector2f(
			static_cast<float>(janela->getSize().x) / 4.f,
			static_cast<float>(janela->getSize().y)
		)
	);
	this->container.setFillColor(sf::Color::Blue);
	this->container.setPosition(
		static_cast<float>(janela->getSize().x) / 2.f - this->container.getSize().x / 2.f,
		0.f
	);
}

/*Construtora e Destrutora*/
MenuPause::MenuPause(sf::RenderWindow* janela, std::stack<Estado*>* estados)
{
	this->janela = janela;
	this->estados = estados;
	this->iniBotoes();
	this->iniFontes();
	this->iniPlanoDeFundo(janela);

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
	atualizaBotoes();
	atualizaPosicaoMouse();

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

void MenuPause::atualizaBotoes()
{
	/*atualiza todos os botoes desse estado e cuida das suas funcionalidades*/
	//main loop
	for (auto& it : this->botoes)
	{
		it.second->update(this->mousePosView);
	}

	//editor
	if (this->botoes["DESPAUSAR"]->isPressed())
	{
		this->estados->top()->despausaEstado();
	}

	//new game
	if (this->botoes["SALVAR"]->isPressed())
	{
		this->estados->top()->salva();
	}

	//quit the game
	if (this->botoes["SAIR"]->isPressed())
	{
		this->estados->top()->fechaEstado();
	}
}

void MenuPause::atualizaPosicaoMouse()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->janela);
	this->mousePosView = this->janela->mapPixelToCoords(sf::Mouse::getPosition(*this->janela));
}
