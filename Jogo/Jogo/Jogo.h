#pragma once
//#include"UIManager.h"
#include"EstadoFase.h"
#include"EstadoMenuPrincipal.h"
#include "GraphicsSettings.h"

class Jogo
{
private:

	/*Variaveis*/
	GraphicsSettings gfxSettings;
	DataEstado data_estado;
	sf::RenderWindow* janela;
	sf::Event evento;

	//UIManager ui_manager;

	

	sf::Clock tdRelogio;
	float td; //tempo delta ou variacao de tempo

	std::stack<Estado*> estados;
	std::map<std::string,int> teclasDisponiveis;

	float gridSize;

	/*Funções Inicializadoras*/
	void iniVariaveis();
	void iniGraphicsSettings();
	void iniJanela();
	void iniTeclas();
	void iniDataEstado();
	void iniEstados();

	//void iniSprites();

public:
	/*Construtora e destrutora*/
	Jogo();
	~Jogo();

	/*Funções*/
	void atualizaTd();
	void atualizaEventosSFML();
	void atualiza();
	void renderiza();

	/**principal**/
	void executa();
};

