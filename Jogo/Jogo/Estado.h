#pragma once
#include "stdafx.h"
#include "Jogador.h"
#include "GraphicsSettings.h"

class Jogador;
class GraphicsSettings;
class Estado;

class DataEstado
{
public:
	DataEstado() {};

	//Variaveis
	float gridSize;

	std::map<std::string, int>* teclasDisponiveis;
	GraphicsSettings* gfxSettings;	//PONTEIRO?
	sf::RenderWindow* janela;
	std::stack<Estado*>* estados;
	bool cooperativo;

};

class Estado
{
private:


protected:
	DataEstado* dataEstado;

	/*Variaveis*/
	std::stack<Estado*>* estados;	//Pilha de estados
	sf::RenderWindow* janela;	//janela do estado
	std::map<std::string, int>* teclasDisponiveis;
	std::map<std::string, int> teclas;
	std::map<std::string, sf::Texture> textures;

	sf::Vector2i mousePosScreen;	//posicao do mouse relativo a tela
	sf::Vector2i mousePosWindow;	//posicao do mouse relativo a janela
	sf::Vector2f mousePosView;		//posicao do mouse relativo a visao atual
	sf::Vector2u mousePosGrid;

	sf::Font font;

	int pontuacao;

	/*Flags*/
	bool sair; //para fechar o estado
	bool cooperativo; //para iniciar o modo de 2 jogadores
	bool ganhou;
	bool pausado;

	float keytime;
	float keytimemax;

	float gridSize;

	/*Funçõees inicializadoras*/
	virtual void iniTeclas() = 0; // cada estado vai definir a utilizacao das teclas
	void iniFontes();

public:
	/*Construtora e destrutora*/
	Estado(DataEstado* data_estado);
	virtual ~Estado();

	/*Set's e Get's*/
	const bool& getSair() const;
	const bool& getCoop() const;
	const bool& getGanhou() const;
	const bool& getPausado() const;
	void setPontuacao(const int pont);
	const int getPontuacao();
	const bool& getKeytime();

	/*Funções*/
	void fechaEstado();
	void pausaEstado();
	void despausaEstado();

	virtual void atualiza(const float& td) = 0;
	virtual void renderiza(sf::RenderTarget* target = NULL) = 0;
	virtual void atualizaTecla(const float& td);
	virtual void atualizaPosicaoMouse(sf::View* view = NULL);
	virtual void updateKeyTime(const float& td);
	virtual void salva() = 0;
};
