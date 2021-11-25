#include "stdafx.h"
#include "Jogo.h"
#include "GraphicsSettings.h"

/*Inicializadores*/

/*void Jogo::iniSprites()
{
	UIManager ui_manager;
	ui_manager.Initialize();
}*/

void Jogo::iniVariaveis()
{
	this->janela = NULL;

	this->td = 0.f;

	this->gridSize = 66.f;
}

void Jogo::iniGraphicsSettings()
{
	this->gfxSettings.loadFromFile("Config/graphics.ini");


}

void Jogo::iniJanela()
{
	//Cria janela a partir da file window.ini


	if(this->gfxSettings.fullscreen)
		this->janela = new sf::RenderWindow(
			this->gfxSettings.resolution, 
			this->gfxSettings.title, 
			sf::Style::Fullscreen,
			this->gfxSettings.contextSettings);
	else
		this->janela = new sf::RenderWindow(
			this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Titlebar | sf::Style::Close,
			this->gfxSettings.contextSettings);

	this->janela->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->janela->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
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

void Jogo::iniDataEstado()
{
	this->data_estado.janela = this->janela;
	this->data_estado.gfxSettings = &this->gfxSettings;
	this->data_estado.teclasDisponiveis = &this->teclasDisponiveis;
	this->data_estado.estados = &this->estados;
	this->data_estado.gridSize = this->gridSize;
}

void Jogo::iniEstados()
{
	//Inicia a pilha de estados empilhando o primeiro estado (menu?)
	this->estados.push(new EstadoMenuPrincipal(&this->data_estado));//, &ui_manager)); //, false
}

/*Construtora e Destrutora*/
Jogo::Jogo()
{
	this->iniVariaveis();
	this->iniGraphicsSettings();
	this->iniJanela();
	this->iniTeclas();
	this->iniDataEstado();
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