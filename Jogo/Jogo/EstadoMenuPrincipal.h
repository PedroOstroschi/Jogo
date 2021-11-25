#ifndef ESTADOMENUPRINCIPAL_H
#define ESTADOMENUPRINCIPAL_H

#include "EstadoEditor.h"
#include "EstadoFase1.h"
#include "EstadoConfig.h"
#include "GUI.h"
#include "GraphicsSettings.h"

class EstadoMenuPrincipal :
	public Estado
{
private:
	/*Variaveis*/
	sf::Texture texturaPlanoDeFundo;
	sf::RectangleShape planoDeFundo;

	std::map<std::string, gui::Botao*> botoes;

	/*Funçõees inicializadoras*/
	void initVariaveis();
	void initPlanoDeFundo();
	void iniTeclas();
	void iniBotoes();

protected:
	sf::Sprite sprite;

public:
	/*Construtora e destrutora*/
	EstadoMenuPrincipal(DataEstado* data_estado);
	virtual ~EstadoMenuPrincipal();

	/*Funções*/
	void atualizaTeclas(const float td);
	void atualizaBotoes();
	void atualiza(const float& td) override; //chama atualizaTecla
	void renderizaBotoes(sf::RenderTarget& alvo);
	void renderiza(sf::RenderTarget* alvo = NULL);
	void salva() {}
};

#endif