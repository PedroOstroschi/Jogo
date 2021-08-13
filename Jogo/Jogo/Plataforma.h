#pragma once
#include "Entidade.h"
class Plataforma :
    public Entidade
{
private:


public:
    Plataforma(/*sf::Texture& textura, */sf::Vector2f posicao, sf::Vector2f desCorpo, sf::Vector2f tamanhoCorpo, bool transparente);
    ~Plataforma();
};

