#pragma once
#include "Entidade.h"
class Plataforma :
    public Entidade
{
private:


public:
    /*sf::Texture& textura, */
    /*tamanho, posicao*/
    Plataforma(sf::Vector2f posicao, sf::Vector2f desCorpo, sf::Vector2f tamanhoCorpo, bool transparente);
    ~Plataforma();
};

