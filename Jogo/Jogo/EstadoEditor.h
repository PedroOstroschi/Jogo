#ifndef ESTADOEDITOR_H
#define ESTADOEDITOR_H

#include "Estado.h"
#include "GUI.h"
#include "MenuPause.h"
#include "TileMap.h"

class State;
class GUI;
class MenuPause;
class TileMap;

class EstadoEditor :
    public Estado
{
private:
	/*Variaveis*/
	sf::View view;

	sf::Text cursorText;
	MenuPause* menupause;

	std::map<std::string, gui::Botao*> botoes;

	TileMap* tileMap;

	sf::RectangleShape sidebar;

	sf::RectangleShape selectorRect;

	gui::TextureSelector* textureSelector;

	sf::IntRect textureRect;
	float cameraSpeed;
	bool colisao;
	short tipo;

	/*Funçõees inicializadoras*/
	void initVariaveis();
	void iniView();
	void initPlanoDeFundo();
	void iniTextos();
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
	void updateGui(const float& td);
	void updatePauseMenuBotoes();
	void atualiza(const float& td) override; //chama atualizaTecla
	void renderizaBotoes(sf::RenderTarget& alvo);
	void renderizaGui(sf::RenderTarget& alvo);
	void renderiza(sf::RenderTarget* alvo = NULL);

	void salva() {}
};

#endif