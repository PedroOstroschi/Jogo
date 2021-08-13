#pragma once
#include "EntidadeDinamica.h"
class Jogador :
    public EntidadeDinamica
{
private:
    /*Variaveis*/


    /*Funcoes Inicializadoras*/
    void iniVariaveis();
    void iniComponentes();

public:
    Jogador(float x, float y, sf::Texture& textura);
    virtual ~Jogador();

    /*Funcoes*/
};

