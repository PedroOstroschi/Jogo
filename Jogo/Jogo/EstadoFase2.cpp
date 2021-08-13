#include "EstadoFase2.h"

/*Construtora e Destrutora*/
EstadoFase2::EstadoFase2(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados)
	:EstadoJogo(teclasDisponiveis, janela, estados)//, cooperativo)
{

}

EstadoFase2::~EstadoFase2()
{

}