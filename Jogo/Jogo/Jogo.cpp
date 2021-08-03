// Jogo.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//


#include "Jogo.h"


//funcoes estaticas

//inicializadora
void Jogo::iniJanela()
{   
    this->janela = new sf::RenderWindow(sf::VideoMode(800, 600), "C++ Jogo");
    //configuracoes da janela
    this->janela->setFramerateLimit(120);
    this->janela->setVerticalSyncEnabled(false);

}

void Jogo::iniEstados()
{   
    //coloca os estados na pilha original de estados
    this->estados.push(new Estado(this->janela, &this->estados, false));
}

//construtora/destrutora
Jogo::Jogo() 
{
    this->iniJanela();
    this->iniEstados();

}
Jogo::~Jogo() 
{
    delete this->janela;

    while (!this->estados.empty())
    {  
        delete this->estados.top();
        this->estados.pop();

    }
}

//funcoes



void Jogo::atualizaTd()
{
    //atualiza a variavel td com tempo que demora para atualizar e renderizar um quadro
    this->td = this->tdRelogio.restart().asSeconds();
    system("cls");
    std::cout << this->td << "\n";
}


void Jogo::atualizaEventosSFML()
{

    while (this->janela->pollEvent(this->evento))
    {
        if (this->evento.type == sf::Event::Closed)
            this->janela->close();
    }


}

void Jogo::atualiza()
{
    this->atualizaEventosSFML();

    if (!this->estados.empty()) 
    {
        this->estados.top()->atualiza(td);

        //se o estado quiser fechar
        if (this->estados.top()->getSair())
        {
            delete this->estados.top();
            this->estados.pop();
        }
        

    }
}

void Jogo::renderiza()
{
    this->janela->clear();

    //renderiza o jogo
    if (!this->estados.empty()) { this->estados.top()->renderiza(); }
    this->janela->display();
}

void Jogo::rodaJogo()
{

    while (this->janela->isOpen())
    {
        this->atualizaTd();
        this->atualiza();
        this->renderiza();

    }
}
