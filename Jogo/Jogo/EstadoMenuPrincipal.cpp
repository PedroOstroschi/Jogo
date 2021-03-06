#include "stdafx.h"
#include "EstadoMenuPrincipal.h"
#include "GraphicsSettings.h"
#include "GUI.h"

/*Inicializadores*/
void EstadoMenuPrincipal::initVariaveis()
{

}

void EstadoMenuPrincipal::initPlanoDeFundo()
{
	this->planoDeFundo.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->janela->getSize().x),
			static_cast<float>(this->janela->getSize().y)
		)
	);

	if (!this->texturaPlanoDeFundo.loadFromFile("Resources/Images/Backgrounds/background.png"))
	{
		throw "ERRO::ESTADO_MENU_PRINCIPAL::FALHOU_CARREGAR_TEXTURA_BACKGROUND";
	}

	this->planoDeFundo.setTexture(&this->texturaPlanoDeFundo);
}

void EstadoMenuPrincipal::iniTeclas()
{
	std::ifstream ifs("Config/estado_menu_teclas.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->teclas[key] = this->teclasDisponiveis->at(key2);
		}
	}

	ifs.close();
}

void EstadoMenuPrincipal::iniBotoes()
{
	this->botoes["EDITOR"] = new gui::Botao(200.f, 200.f, 200.f, 200.f,
		&this->font, "EDITOR", 24,
		sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)
	);	
	
	this->botoes["FASE_1"] = new gui::Botao(802.f, 700.f, 150.f, 50.f,
		&this->font, "Novo Jogo", 24,
		sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
	
	this->botoes["FASE_2"] = new gui::Botao(970.f, 700.f, 150.f, 50.f,
		&this->font, "Selecionar Fase", 24,
		sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
		
	this->botoes["CONFIG"] = new gui::Botao(802.f, 770.f, 150.f, 50.f,
		&this->font, "Configurações", 24,
		sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

	this->botoes["SAIR"] = new gui::Botao(970.f, 770.f, 150.f, 50.f,
		&this->font, "Sair", 24,
		sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));
}

/*Construtora e Destrutora*/
EstadoMenuPrincipal::EstadoMenuPrincipal(DataEstado* data_estado)
	: Estado(data_estado)
{
	this->initVariaveis();
	this->initPlanoDeFundo();
	this->iniFontes();
	this->iniTeclas();
	this->iniBotoes();
}

EstadoMenuPrincipal::~EstadoMenuPrincipal()
{
	auto it = this->botoes.begin();
	for (it = this->botoes.begin(); it != this->botoes.end(); ++it)
	{
		delete it->second;
	}
}

/*Funções*/

void EstadoMenuPrincipal::atualizaTeclas(const float td)
{
	//atualiza entrada do jogador
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		std::cout << "asasa" << "\n";
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("FECHAR"))))
		this->fechaEstado();
}

void EstadoMenuPrincipal::atualiza(const float& td)
{
	this->atualizaTeclas(td);
	this->atualizaPosicaoMouse();
	this->atualizaBotoes();
}

void EstadoMenuPrincipal::renderiza(sf::RenderTarget* alvo)
{
	//alvo esta como ponteiro nulo
	if (alvo == NULL)
		alvo = this->janela;

	alvo->draw(this->planoDeFundo);

	this->renderizaBotoes(*alvo);

	//REMOVE
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x + 10, this->mousePosView.y + 15);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(24);
	mouseText.setFillColor(sf::Color::Black);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	alvo->draw(mouseText);
}

void EstadoMenuPrincipal::atualizaBotoes()
{
	/*atualiza todos os botoes desse estado e cuida das suas funcionalidades*/
	//main loop
	for (auto& it : this->botoes)
	{
		it.second->update(this->mousePosWindow);
	}

	//editor
	if (this->botoes["EDITOR"]->isPressed())
	{
		this->estados->push(new EstadoEditor(this->dataEstado));
	}

	//new game
	if (this->botoes["FASE_1"]->isPressed())
	{
		this->estados->push(new EstadoFase1(this->dataEstado));
		//this->estados->push(new Fase1()/*this->teclasDisponiveis, this->janela, this->estados)*/);
	}
	
	//select stage
	if (this->botoes["FASE_2"]->isPressed())
	{
		this->estados->push(new EstadoFase(this->dataEstado));
	}
	
	//config menu
	if (this->botoes["CONFIG"]->isPressed())
	{
		this->estados->push(new EstadoConfig(this->dataEstado));
	}

	//quit the game
	if (this->botoes["SAIR"]->isPressed())
	{
		this->sair = true;
	}
}

void EstadoMenuPrincipal::renderizaBotoes(sf::RenderTarget& alvo)
{
	for (auto& it : this->botoes)
	{
		it.second->render(alvo);
	}
}