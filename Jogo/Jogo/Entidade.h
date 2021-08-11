#pragma once
#include <stdlib.h>
#include <iostream>
#include"SFML/Graphics.hpp"

class Entidade
{
private:
	void initVariaveis();
protected:
	/*Variaveis*/

	sf::Sprite sprite;

public:
	/*Construtora e destrutora*/
	Entidade();
	virtual ~Entidade();

	/*Funções de Componente*/
	void setTexture(sf::Texture& texture);

	/*Funções*/
	virtual void setPosition(const float x, const float y);
	virtual void renderiza(sf::RenderWindow* alvo);
};
