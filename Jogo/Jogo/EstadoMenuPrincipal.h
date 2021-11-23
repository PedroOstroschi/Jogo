#pragma once
#include "EstadoEditor.h"
#include "EstadoFase1.h"
#include "EstadoConfig.h"
#include "GUI.h"
class EstadoMenuPrincipal :
	public Estado
{
private:
	/*Variaveis*/
	sf::Texture texturaPlanoDeFundo;
	sf::RectangleShape planoDeFundo;

	std::map<std::string, gui::Botao*> botoes;

	/*Fun��ees inicializadoras*/
	void initVariaveis();
	void initPlanoDeFundo();
	void iniTeclas();
	void iniBotoes();

protected:
	sf::Sprite sprite;

public:
	/*Construtora e destrutora*/
	EstadoMenuPrincipal(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados);// , UIManager* ui_manager);
	virtual ~EstadoMenuPrincipal();

	/*Fun��es*/
	void atualizaTeclas(const float td);
	void atualizaBotoes();
	void atualiza(const float& td) override; //chama atualizaTecla
	void renderizaBotoes(sf::RenderTarget& alvo);
	void renderiza(sf::RenderTarget* alvo = NULL);
	void salva() {}
};
