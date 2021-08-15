#pragma once
#include "EntidadeDinamica.h"


class Inimigo1 :
    public EntidadeDinamica
{
private:


protected:
    /*Variaveis*/
    int HP;

public:
    Inimigo1(float x, float y, sf::Texture& textura);
    virtual ~Inimigo1();
};

