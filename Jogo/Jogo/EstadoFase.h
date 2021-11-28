#pragma once
#include "stdafx.h"
#include "Estado.h"
#include "Jogador.h"
#include "MenuPause.h"
#include "TileMap.h"

class ManuPause;
class Jogador;
class TileMap;
class sf::View;
class sf::Font;
class sf::RenderTexture;

class EstadoFase :
	public Estado
{
private:

	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	MenuPause* menupause;

	/*Variaveis*/
	Jogador* jogador;
	sf::Texture texture;

	TileMap* tileMap;

	/*Funçõees inicializadoras*/
	void iniPosRender();
	void iniView();
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

	/*Funções*/
	void updateView(const float& td);
	void fechaEstado();
	void pausaEstado();
	void despausaEstado();
	void updatePlayerInput(const float td);
	void updatePauseMenuButtons();
	void updateTileMap(const float& td);
	void atualiza(const float& td) override; //chama atualizaTecla
	void renderiza(sf::RenderTarget* alvo = NULL);
	void gerarFase();
	void gerarInimigos();
	void gerarObstaculos();
	void updateInput(const float& td);

	/* funcoes para salvar */

	void salva();
};
