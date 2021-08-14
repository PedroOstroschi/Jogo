#pragma once
#include "Estado.h"
#include "Botao.h"

class MenuPause
{
private:
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, Botao*> botoes;


public:
	/*Construtora e Destrutora*/
	MenuPause(sf::RenderWindow& janela);
	virtual ~MenuPause();

	/*Funcoes*/
	void atualiza();
	void renderiza(sf::RenderTarget *alvo);
};

