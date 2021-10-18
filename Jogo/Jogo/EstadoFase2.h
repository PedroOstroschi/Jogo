#pragma once
#include "EstadoFase.h"

class EstadoFase2 :
    public EstadoFase
{
private:

protected:

public:
    /*Construtora e destrutora*/
    EstadoFase2(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados);//, cooperativo)
    ~EstadoFase2();

    /*Funcoes*/
    void terminou();
};
