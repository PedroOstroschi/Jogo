#pragma once
#include "stdafx.h"
#include "Estado.h"
#include "Jogador.h"
#include "MenuPause.h"
#include "TileMap.h"

class EstadoFase :
	public Estado
{
private:

	MenuPause* menupause;

	/*Variaveis*/
	Jogador* jogador;
	sf::Texture texture;

	TileMap* tileMap;

	/*Fun��ees inicializadoras*/
	void iniElementos();
	void iniTeclas();
	void iniFontes();
	void iniTexturas();
	void iniJogadores();
	void initPauseMenu();
	void iniTileMap();

protected:
	
	FILE* fase;
public:
	/*Construtora e destrutora*/
	EstadoFase(DataEstado* data_estado );
	virtual ~EstadoFase();

	/*set e get*/

	/*Fun��es*/
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
