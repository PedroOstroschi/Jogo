#pragma once
#include "Botao.h"


class EstadoPausado :
    public Estado
{
private:
    /*variaveis*/
    sf::Texture texturaPlanoDeFundo;
    sf::RectangleShape planoDeFundo;
    std::map<std::string, Botao*> botoes;

    /*inicializadoras*/
    void initVariaveis();
    void initPlanoDeFundo();
    void iniTeclas();
    void iniBotoes();
public:
    /* Construtora e  destrutora*/
    EstadoPausado(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados);
    ~EstadoPausado();

    /*Funcoes*/

    void despausa();
    void atualizaTeclas(const float td);
    void atualiza(const float& td) override; //chama atualizaTecla
    void renderiza(sf::RenderTarget* alvo = NULL);
    void atualizaBotoes();
    void renderizaBotoes(sf::RenderTarget* alvo = NULL);
};

