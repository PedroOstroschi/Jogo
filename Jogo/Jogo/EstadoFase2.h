#pragma once
#include "EstadoFase.h"

class EstadoFase2 :
    public EstadoFase
{
private:

protected:

public:
    /*Construtora e destrutora*/
    EstadoFase2(DataEstado* data_estado);//, cooperativo)
    ~EstadoFase2();

    /*Funcoes*/
    void terminou();
};
