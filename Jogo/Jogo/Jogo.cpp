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
    this->estados.push(new EstadoJogo( &this->teclasDisponiveis, this->janela)); //, &this->estados, false
}

void Jogo::iniTeclas()
{
   
    this->teclasDisponiveis.emplace("A", sf::Keyboard::Key::A);
    this->teclasDisponiveis.emplace("W", sf::Keyboard::Key::W);
    this->teclasDisponiveis.emplace("S", sf::Keyboard::Key::S);
    this->teclasDisponiveis.emplace("D", sf::Keyboard::Key::D);
    this->teclasDisponiveis.emplace("Escape", sf::Keyboard::Key::Escape);

}

//construtora/destrutora
Jogo::Jogo() 
{
    this->iniJanela();
    this->iniTeclas();
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

//funcoes gerais



void Jogo::atualizaTd()
{
    //atualiza a variavel td com tempo que demora para atualizar e renderizar um quadro
    this->td = this->tdRelogio.restart().asSeconds();
    system("cls");
    std::cout << this->td << "\n";
    //std::cout << this->
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
    else
    {
        this->janela->close();
    }
}

void Jogo::renderiza()
{
    this->janela->clear();

    //renderiza o estado atual da pilha
    if (!this->estados.empty())
    {
        this->estados.top()->renderiza();
    }
 
    this->janela->display();
}

void Jogo::executa()
{

    while (this->janela->isOpen())
    {
        this->atualizaTd();
        this->atualiza();//loop principal
        this->renderiza();

    }
}
