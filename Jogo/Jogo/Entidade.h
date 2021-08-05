#pragma once
#include <stdlib.h>
#include <iostream>
#include"SFML/Graphics.hpp"

class Entidade
{
private:

protected:
	sf::RectangleShape forma;



public:
	//Construtora/Destrutora
	Entidade();
	virtual~Entidade();

	//Funcoes gerais
	virtual void renderiza(sf::RenderTarget& alvo);


};

