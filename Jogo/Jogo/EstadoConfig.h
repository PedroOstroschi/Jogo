#pragma once

#ifndef ESTADOCONFIG_H
#define ESTADOCONFIG_H

#include "Estado.h"
#include "GUI.h"

class EstadoConfig :
	public Estado
{
private:
	/*Variaveis*/
	sf::Texture texturaPlanoDeFundo;
	sf::RectangleShape planoDeFundo;

	std::map<std::string, gui::Botao*> botoes;
	std::map<std::string, gui::DropDownList*> dropDownListas;

	sf::Text optionsText;

	std::vector<sf::VideoMode> modes;

	/*Funçõees inicializadoras*/
	void initVariaveis();
	void initPlanoDeFundo();
	void iniTeclas();
	void iniGui();
	void iniTexto();

public:
	EstadoConfig(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados);
	virtual ~EstadoConfig();

	//Accessors


	//Functions
	void atualizaTeclas(const float td);
	void atualizaGui(const float td);
	void atualiza(const float& td) override; //chama atualizaTecla
	void renderizaGui(sf::RenderTarget& alvo);
	void renderiza(sf::RenderTarget* alvo = NULL);
	void salva();
};

#endif