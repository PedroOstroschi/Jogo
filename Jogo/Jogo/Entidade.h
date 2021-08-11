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

	/*Fun��es de Componente*/
	void setTexture(sf::Texture& texture);

	/*Fun��es*/
	virtual void setPosition(const float x, const float y);
	virtual void renderiza(sf::RenderWindow* alvo);
};
