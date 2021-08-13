#include "EstadoFase1.h"

/*Construtora e Destrutora*/
EstadoFase1::EstadoFase1(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados)
	:EstadoJogo(teclasDisponiveis, janela, estados)//, cooperativo)
{
	
}

EstadoFase1::~EstadoFase1()
{

}