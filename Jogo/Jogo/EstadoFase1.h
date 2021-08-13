#pragma once
#include "EstadoFase.h"

class EstadoFase1 :
    public EstadoFase
{
private:

protected:

public:
    /*Construtora e destrutora*/
    EstadoFase1(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados);//, cooperativo)
    ~EstadoFase1();
};
