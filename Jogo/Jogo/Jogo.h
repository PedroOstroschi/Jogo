#pragma once
#include"Estado.h"
#include"EstadoJogo.h"

class Jogo
{
private:
	//variaveis
	sf::RenderWindow* janela;
	sf::Event evento;

	sf::Clock tdRelogio;
	float td; //tempo delta ou variacao de tempo

	std::stack<Estado*> estados;
	std::map < std::string , int > teclasDisponiveis;



	//inicializacao
	void iniJanela();
	void iniEstados();
	void iniTeclas();

public:
	//construtora/destrutora
	Jogo();
	~Jogo();

	//funcoes gerais
	void atualizaTd();
	void atualizaEventosSFML();
	void atualiza();
	void renderiza();

	//principal
	void executa();
};

