#pragma once
#include "EntidadeDinamica.h"

class Colisor
{
private:
	sf::RectangleShape& corpo;
	sf::Sprite& sprite;

public:
	/*Construtora e destrutora*/
	Colisor(sf::Sprite& sprite, sf::RectangleShape& corpo);
	~Colisor();

	bool verificaColisao(Colisor& outroCorpo, sf::Vector2f& direcao, float repulsao);
	sf::Vector2f getMetadeDoTamanho() 
	{
		return corpo.getSize() / 2.f;
	}
	void move(float variacaoX, float variacaoY)
	{
		sprite.move(variacaoX, variacaoY);
	}
	
};

