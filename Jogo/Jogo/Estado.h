#pragma once
#include<stack>
#include<map>
#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

using namespace std;
class Estado
{
protected:
	//variaveis
	stack<Estado*>* estados; //Pilha de estados
	sf::RenderWindow* janela;//janela do estado
	int pontuacao;

	//flags
	bool sair; //par fecahr o estado
	bool cooperativo; //para iniciar o modo de 2 jogadores
	bool ganhou;
	bool pausado;

	

public:
	//construtora/destrutora
	Estado(sf::RenderWindow* janela, std::stack<Estado*>* estados, bool cooperativo);
	virtual ~Estado();

	//set`s/get`s
	const bool& getSair() const;
	const bool& getCoop() const;
	const bool& getGanhou() const;
	const bool& getPausado() const;
	void setPontuacao(const int pont);
	const int getPontuacao();

	//funcoes gerais
	void fechaEstado();
	void pausaEstado();
	void despausaEstado();
	void atualiza(const float& td);
	void renderiza();
	void atualizaTecla(const float& td);



};

