#pragma once
#include"UIManager.h"
#include"EstadoJogo.h"
#include"EstadoMenuPrincipal.h"

class Jogo
{
private:
	/*Variaveis*/
	sf::RenderWindow* janela;
	sf::Event evento;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;
	//UIManager ui_manager;

	

	sf::Clock tdRelogio;
	float td; //tempo delta ou variacao de tempo

	std::stack<Estado*> estados;
	std::map<std::string,int> teclasDisponiveis;

	/*Funções Inicializadoras*/
	void iniVariaveis();
	void iniJanela();
	void iniTeclas();
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

