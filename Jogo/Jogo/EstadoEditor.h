#ifndef ESTADOEDITOR_H
#define ESTADOEDITOR_H

#include "Estado.h"
#include "GUI.h"
#include "MenuPause.h"
#include "TileMap.h"

//ajuda o pc/compilador/c++?
class State;
class GUI;
class MenuPause;
class TileMap;

////////////////////////////////


class EstadoEditor :
    public Estado
{
private:
	/*Variaveis*/
	std::map<std::string, gui::Botao*> botoes;
	MenuPause* menupause;

	TileMap* tileMap;

	sf::RectangleShape selectorRect;

	/*Funçõees inicializadoras*/
	void initVariaveis();
	void initPlanoDeFundo();
	void iniTeclas();
	void initPauseMenu();
	void iniBotoes();
	void iniGui();
	void iniTileMap();

protected:
	sf::Sprite sprite;

public:
	/*Construtora e destrutora*/
	EstadoEditor(DataEstado* data_estado);
	virtual ~EstadoEditor();

	/*Funções*/
	void atualizaTeclas(const float td);
	void atualizaEditorInput(const float& td);
	void atualizaBotoes();
	void updateGui();
	void updatePauseMenuBotoes();
	void atualiza(const float& td) override; //chama atualizaTecla
	void renderizaBotoes(sf::RenderTarget& alvo);
	void renderizaGui(sf::RenderTarget& alvo);
	void renderiza(sf::RenderTarget* alvo = NULL);

	void salva() {}
};

#endif