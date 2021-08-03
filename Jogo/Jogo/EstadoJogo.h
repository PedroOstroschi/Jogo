#pragma once
#include "Estado.h"
#include <stack>
class EstadoJogo :
    public Estado
{
private:

public:
    //Construtora/ destrutora
    EstadoJogo(sf::RenderWindow* janela);
    virtual ~EstadoJogo();

    //Funcoes
    void fechaEstado();
    void atualiza(const float td); //chama atualizaTecla
    void renderiza();
    void atualizaTeclas(const float td);

};

