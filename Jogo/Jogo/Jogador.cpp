#include "Jogador.h"

/*Funcoes Inicializadoras*/
void Jogador::iniVariaveis()
{

}

void Jogador::iniComponentes()
{
	this->createMovementComponent(200.f, 50.f, 20.f);
}

/*Construtora e Destrutora*/
Jogador::Jogador(float x, float y, sf::Texture& textura)
{
	this->iniComponentes();
	this->iniVariaveis();

	this->setTexture(textura);
	this->setPosition(x, y);
}

Jogador::~Jogador()
{
	
}