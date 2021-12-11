#include "stdafx.h"
#include "EstadoConfig.h"
#include "GraphicsSettings.h"

//init
void EstadoConfig::initVariaveis()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void EstadoConfig::initPlanoDeFundo()
{
	this->planoDeFundo.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->janela->getSize().x),
			static_cast<float>(this->janela->getSize().y)
		)
	);

	if (!this->texturaPlanoDeFundo.loadFromFile("Resources/Images/Backgrounds/background_grafico.png"))
	{
		throw "ERRO::ESTADO_MENU_PRINCIPAL::FALHOU_CARREGAR_TEXTURA_BACKGROUND";
	}

	this->planoDeFundo.setTexture(&this->texturaPlanoDeFundo);
}

void EstadoConfig::iniTeclas()
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

void EstadoConfig::iniGui()
{
	//botoes
	this->botoes["BACK"] = new gui::Botao(
		1500.f, 880.f, 150.f, 50.f,
		&this->font, "Voltar", 24,
		sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)
	);

		this->botoes["APPLY"] = new gui::Botao(
		100.f, 100.f, 150.f, 50.f,
		&this->font, "Aplicar", 24,
		sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200)
	);

	//ddl
	std::vector<std::string> modes_str;
	for (auto& i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}

	this->dropDownListas["RESOLUTION"] = new gui::DropDownList(800, 450, 200, 50, font, modes_str.data(), modes_str.size());
}

void EstadoConfig::iniTexto()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(550.f, 450.f));
	this->optionsText.setCharacterSize(30);
	this->optionsText.setFillColor(sf::Color::Black);


	this->optionsText.setString(
		"Resolution \nFullscreen \nVSync \nAntialiasing"
	);
}

//c&d
EstadoConfig::EstadoConfig(DataEstado* data_estado)
	: Estado(data_estado)
{
	this->initVariaveis();
	this->initPlanoDeFundo();
	this->iniFontes();
	this->iniTeclas();
	this->iniGui();
	this->iniTexto();
}

EstadoConfig::~EstadoConfig()
{
	auto it = this->botoes.begin();
	for (it = this->botoes.begin(); it != this->botoes.end(); ++it)
	{
		delete it->second;
	}
	auto it2 = this->dropDownListas.begin();
	for (it2 = this->dropDownListas.begin(); it2 != this->dropDownListas.end(); ++it2)
	{
		delete it2->second;
	}
}

//Accessors

//Functions
void EstadoConfig::atualizaTeclas(const float td)
{
	//atualiza entrada do jogador
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		std::cout << "asasa" << "\n";
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("FECHAR"))))
		this->fechaEstado();
}

void EstadoConfig::atualizaGui(const float td)
{
	/*atualiza todos os elementos da GUI desse estado e cuida das suas funcionalidades*/
	//BOTOES
	for (auto& it : this->botoes)
	{
		it.second->update(this->mousePosWindow);
	}
	//quit the game
	if (this->botoes["BACK"]->isPressed())
	{
		this->sair = true;
	}
	//aplicar
	if (this->botoes["APPLY"]->isPressed())
	{
		this->dataEstado->gfxSettings->resolution = this->modes[this->dropDownListas["RESOLUTION"]->getActiveElementdId()];
		
		this->janela->create(this->dataEstado->gfxSettings->resolution, this->dataEstado->gfxSettings->title, sf::Style::Default);
	}

	//DDL
	for (auto& it : this->dropDownListas)
	{
		it.second->update(this->mousePosWindow, td);
	}
	//ddl funcionality
}

void EstadoConfig::atualiza(const float& td)
{
	this->atualizaTeclas(td);
	this->atualizaPosicaoMouse();
	this->atualizaGui(td);
}

void EstadoConfig::renderizaGui(sf::RenderTarget& alvo)
{
	//botoes
	for (auto& it : this->botoes)
	{
		it.second->render(alvo);
	}
	//ddl
	for (auto& it : this->dropDownListas)
	{
		it.second->render(alvo);
	}
}

void EstadoConfig::renderiza(sf::RenderTarget* alvo)
{
	//alvo esta como ponteiro nulo
	if (alvo == NULL)
		alvo = this->janela;

	alvo->draw(this->planoDeFundo);

	this->renderizaGui(*alvo);

	alvo->draw(this->optionsText);

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

void EstadoConfig::salva()
{

}