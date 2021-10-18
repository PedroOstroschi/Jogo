#pragma once
#include "Botao.h"

class MenuPause
{
private:
	/*Variaveis*/
	sf::RectangleShape background;
	sf::RectangleShape container;
	std::stack<Estado*>* estados;	//Pilha de estados
	sf::Font font;					//posicao do mouse relativo a visao atual
	sf::RenderWindow* janela;

	sf::Vector2i mousePosScreen;	//posicao do mouse relativo a tela
	sf::Vector2i mousePosWindow;	//posicao do mouse relativo a janela
	sf::Vector2f mousePosView;		//posicao do mouse relativo a visao atual

	/*mapa com os botoes*/
	std::map<std::string, Botao*> botoes;
	
	/*inicializadoras*/
	void iniBotoes();
	void iniFontes();
	void iniPlanoDeFundo(sf::RenderWindow* janela);


public:
	/*Construtora e Destrutora*/
	MenuPause(sf::RenderWindow* janela, std::stack<Estado*>* estados);
	virtual ~MenuPause();

	/*Funcoes*/
	void atualiza();
	void renderiza(sf::RenderTarget *alvo);
	void atualizaBotoes();
	void atualizaPosicaoMouse();
};

