#ifndef ESTADOEDITOR_H
#define ESTADOEDITOR_H

#include "Estado.h"
#include "Botao.h"

class EstadoEditor :
    public Estado
{
private:
	/*Variaveis*/
	std::map<std::string, Botao*> botoes;

	/*Fun��ees inicializadoras*/
	void initVariaveis();
	void initPlanoDeFundo();
	void iniTeclas();
	void iniBotoes();

protected:
	sf::Sprite sprite;

public:
	/*Construtora e destrutora*/
	EstadoEditor(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados);
	virtual ~EstadoEditor();

	/*Fun��es*/
	void atualizaTeclas(const float td);
	void atualiza(const float& td) override; //chama atualizaTecla
	void renderiza(sf::RenderTarget* alvo = NULL);
	void atualizaBotoes();
	void renderizaBotoes(sf::RenderTarget& alvo);
	void salva() {}
};

#endif