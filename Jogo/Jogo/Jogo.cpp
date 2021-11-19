// Jogo.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.

#include "Jogo.h"

/*Inicializadores*/

/*void Jogo::iniSprites()
{
	UIManager ui_manager;
	ui_manager.Initialize();
}*/

void Jogo::iniVariaveis()
{
	this->janela = NULL;
	this->fullscreen = false;
	this->td = 0.f;
}

void Jogo::iniJanela()
{
	//Cria janela a partir da file window.ini
	std::ifstream config("Config/window.ini");
	this->videoModes = sf::VideoMode::getFullscreenModes();

	//Infos tiradas da window_config.ini
	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	//Tira as informações da file	
	if (config.is_open())
	{
		std::getline(config, title);
		config >> window_bounds.width >> window_bounds.height;
		config >> fullscreen;
		config >> framerate_limit;
		config >> vertical_sync_enabled;
		config >> antialiasing_level;
	}
	config.close();

	//Inicializa a janela
	this->fullscreen = fullscreen;
	this->windowSettings.antialiasingLevel = antialiasing_level;

	if(this->fullscreen)
		this->janela = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
	else
		this->janela = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	this->janela->setFramerateLimit(framerate_limit);
	this->janela->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Jogo::iniTeclas()
{
	//Lê as teclas disponíveis
	std::ifstream ifs("Config/teclasDisponiveis.ini");

	//Inicia as teclas disponiveis pelo window_config.ini  
	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->teclasDisponiveis[key] = key_value;
		}
	}
	ifs.close();

	/*debug*/	
		//printar todas as teclas
		for (auto i : this->teclasDisponiveis)
		{
			std::cout << i.first << " " << i.second << "\n";
		}
}

void Jogo::iniEstados()
{
	//Inicia a pilha de estados empilhando o primeiro estado (menu?)
	this->estados.push(new EstadoMenuPrincipal(&this->teclasDisponiveis, this->janela, &this->estados));//, &ui_manager)); //, false
}

/*Construtora e Destrutora*/
Jogo::Jogo()
{
	this->iniJanela();
	this->iniTeclas();
	this->iniEstados();
}

Jogo::~Jogo()
{
	delete this->janela;

	while (!this->estados.empty())
	{
		delete this->estados.top();
		this->estados.pop();
	}
}

/*Funções*/
void Jogo::atualizaTd()
{
	/*TD = FPS = FRAMERATE*/
	//atualiza a variavel td com tempo que demora para atualizar e renderizar um quadro
	this->td = this->tdRelogio.restart().asSeconds();
	system("cls");
	std::cout << this->td << "\n";
}

void Jogo::atualizaEventosSFML()
{
	while (this->janela->pollEvent(this->evento))
	{
		if (this->evento.type == sf::Event::Closed)
			this->janela->close();
	}
}

void Jogo::atualiza()
{
	this->atualizaEventosSFML();

	if (!this->estados.empty())
	{
		this->estados.top()->atualiza(td);

		//se o estado quiser fechar
		if (this->estados.top()->getSair())
		{
			delete this->estados.top();
			this->estados.pop();
		}
	}
	else
	{
		this->janela->close();
	}
}

void Jogo::renderiza()
{
	this->janela->clear();

	//renderiza o estado atual da pilha
	if (!this->estados.empty())
	{
		this->estados.top()->renderiza();
	}

	this->janela->display();
}

void Jogo::executa()
{
	while (this->janela->isOpen())
	{
		this->atualizaTd();
		this->atualiza();//loop principal
		this->renderiza();
	}
}