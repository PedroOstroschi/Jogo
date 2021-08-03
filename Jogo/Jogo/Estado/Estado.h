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
	stack<Estado*> estados;
	sf::RenderWindow* janela;
	//flags
	bool sair; //flag apra sair
	bool cooperativo; //flag par 2 jogadores
	bool ganhou; // flag para ganhar
	bool pausado;
	

public:
	//construtora/destrutora
	Estado(sf::RenderWindow* janela);
	virtual ~Estado();

	//get`s
	const bool& getSair() const;
	const bool& getCoop() const;
	const bool& getGanhou() const;

	//funcoes gerais
	void fechaEStado();
	void pausaEstado();
	void despausaEStado();
	void atualiza(const float& td);
	void renderiza();
	void



};

