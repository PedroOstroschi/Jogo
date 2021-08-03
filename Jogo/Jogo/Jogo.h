#pragma once
#include"Estado.h"

class Jogo
{
private:
	//variaveis
	sf::RenderWindow* janela;
	sf::Event evento;

	sf::Clock tdRelogio;
	float td; //tempo delta ou variacao de tempo

	std::stack<Estado*> estados;



	//inicializacao
	void iniJanela();
	void iniEstados();

public:
	//construtora/destrutora
	Jogo();
	~Jogo();

	//funcoes
	void atualizaTd();
	void atualizaEventosSFML();
	void atualiza();
	void renderiza();
	void rodaJogo();
};

