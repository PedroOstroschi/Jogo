#pragma once
#include "Estado.h"
#include "Jogador.h"
#include "MenuPause.h"

#include"Plataforma.h"

#include <stack>

class EstadoFase :
	public Estado
{
private:
	

	MenuPause menupause;

	/*Variaveis*/
	Jogador* jogador;

	char LinhaAtual[100];


	/*Fun��ees inicializadoras*/
	void iniElementos();
	void iniTeclas();
	void iniTexturas();
	void iniJogadores();
protected:
	
	FILE* fase;
public:
	/*Construtora e destrutora*/
	EstadoFase(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados);
	virtual ~EstadoFase();

	/*set e get*/

	/*Fun��es*/
	void fechaEstado();
	void pausaEstado();
	void despausaEstado();
	void atualizaTeclas(const float td);
	void atualiza(const float& td) override; //chama atualizaTecla
	void renderiza(sf::RenderTarget* alvo = NULL);
	void gerarFase();
	void gerarInimigos();
	void gerarObstaculos();

	/* funcoes para salvar */

	void salva();
};
