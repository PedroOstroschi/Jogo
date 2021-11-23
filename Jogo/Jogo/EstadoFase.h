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
	


	MenuPause* menupause;

	/*Variaveis*/
	Jogador* jogador;
	sf::Texture texture;

	/*Funçõees inicializadoras*/
	void iniElementos();
	void iniTeclas();
	void iniFontes();
	void iniTexturas();
	void iniJogadores();
	void initPauseMenu();

protected:
	
	FILE* fase;
public:
	/*Construtora e destrutora*/
	EstadoFase(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados);
	virtual ~EstadoFase();

	/*set e get*/

	/*Funções*/
	void fechaEstado();
	void pausaEstado();
	void despausaEstado();
	void updatePlayerInput(const float td);
	void updatePauseMenuButtons();
	void atualiza(const float& td) override; //chama atualizaTecla
	void renderiza(sf::RenderTarget* alvo = NULL);
	void gerarFase();
	void gerarInimigos();
	void gerarObstaculos();
	void updateInput(const float& td);

	/* funcoes para salvar */

	void salva();
};
