#pragma once
#include "Estado.h"
#include "Jogador.h"
#include <stack>

class EstadoJogo :
	public Estado
{
private:
	/*Variaveis*/
	Jogador* jogador;

	/*Funçõees inicializadoras*/
	void iniTeclas();
	void iniTexturas();
	void iniJogadores();

public:
	/*Construtora e destrutora*/
	EstadoJogo(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados);
	virtual ~EstadoJogo();

	/*Funções*/
	void fechaEstado();
	void atualizaTeclas(const float td);
	void atualiza(const float& td) override; //chama atualizaTecla
	void renderiza(sf::RenderTarget* alvo = NULL);
};
