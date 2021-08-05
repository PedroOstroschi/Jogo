#pragma once
#include "Entidade.h"
class EntidadeDinamica :
    public Entidade
{
private:

protected:
    float velocidade;
public:
    //Construtora / Destrutora
    EntidadeDinamica();
    virtual~EntidadeDinamica();

    //Funcoes
    void move(const float& td, const float dir_x, const float dir_y);



};

