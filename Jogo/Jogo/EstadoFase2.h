#pragma once
#include "EstadoJogo.h"

class EstadoFase2 :
    public EstadoJogo
{
private:

protected:

public:
    /*Construtora e destrutora*/
    EstadoFase2(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados);//, cooperativo)
    ~EstadoFase2();
};
