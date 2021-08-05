#pragma once
#include "Estado.h"
#include "EntidadeDinamica.h"
#include <stack>
class EstadoJogo :
    public Estado
{
private:
    //variaveis
    EntidadeDinamica* jogador;

    //funcoes inicializadoras
    void iniTeclas();

public:
    //Construtora/ destrutora
    EstadoJogo(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela);
    virtual ~EstadoJogo();

    //Funcoes
    void fechaEstado();
    void atualiza(const float td); //chama atualizaTecla
    void renderiza(sf::RenderTarget* alvo  = NULL);
    void atualizaTeclas(const float td );

};

