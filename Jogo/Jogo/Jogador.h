#pragma once
#include "EntidadeDinamica.h"
class Jogador :
    public EntidadeDinamica
{
private:
    /*Variaveis*/
    bool attacking;

    /*Funcoes Inicializadoras*/
    void iniVariaveis();
    void iniComponentes();

public:
    Jogador(float x, float y, sf::Texture& texture_sheet);
    virtual ~Jogador();

    /*Funcoes*/
    void updateAttack();
    void updateAnimation(const float& dt);
    virtual void atualiza(const float& dt);
};

