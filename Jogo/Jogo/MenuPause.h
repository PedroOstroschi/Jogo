#pragma once
#include "GUI.h"

class MenuPause
{
private:
	/*Variaveis*/
	sf::RectangleShape background;
	sf::RectangleShape container;
	std::stack<Estado*>* estados;	//Pilha de estados
	sf::Font& font;					//posicao do mouse relativo a visao atual
	sf::Text textoMenuPause;
	sf::RenderWindow* janela;

	sf::Vector2i mousePosScreen;	//posicao do mouse relativo a tela
	sf::Vector2i mousePosWindow;	//posicao do mouse relativo a janela
	sf::Vector2f mousePosView;		//posicao do mouse relativo a visao atual

	/*mapa com os botoes*/
	std::map<std::string, gui::Botao*> botoes;
	
	/*inicializadoras*/
	void iniBotoes();
	void iniFontes();
	void iniPlanoDeFundo(sf::RenderWindow* janela);


public:
	/*Construtora e Destrutora*/
	MenuPause(sf::RenderWindow* janela, sf::Font& font);
	virtual ~MenuPause();

	//Accessors
	std::map<std::string, gui::Botao*>& getButtons();

	/*Funcoes*/
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void atualiza(const sf::Vector2i& mousePosWindow);
	void renderiza(sf::RenderTarget& alvo);
	void atualizaBotoes();
	void atualizaPosicaoMouse();
};

