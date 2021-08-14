#pragma once
#include "Jogador.h"
#include "ListaEntidade.h"
#include "EstadoPausado.h"
#include "MenuPause.h"
#include <stack>

class EstadoFase :
	public Estado
{
private:

	MenuPause menupause;

	/*Variaveis*/
	Jogador* jogador;
	ListaEntidade* listaEntidades;

	/*Funçõees inicializadoras*/
	void iniElementos();
	void iniTeclas();
	void iniTexturas();
	void iniJogadores();

public:
	/*Construtora e destrutora*/
	EstadoFase(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados);
	virtual ~EstadoFase();

	/*set e get*/
	ListaEntidade* getListaEntidade() { return listaEntidades; }

	/*Funções*/
	void fechaEstado();
	void pausaEstado();
	void atualizaTeclas(const float td);
	void atualiza(const float& td) override; //chama atualizaTecla
	void renderiza(sf::RenderTarget* alvo = NULL);

	/* funcoes para salvar */

	void salva();
};
