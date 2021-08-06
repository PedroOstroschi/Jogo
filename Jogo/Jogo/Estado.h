#pragma once
#include<stack>
#include<map>
#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>

using namespace std;
class Estado
{
private:

protected:
	//variaveis
	stack<Estado*>* estados; //Pilha de estados
	sf::RenderWindow* janela;//janela do estado
	std::map<std::string, int>* teclasDisponiveis;
	std::map<std::string, int> teclas;
	std::vector<sf::Texture> textures;
	

	//Recursos
	int pontuacao;

	//flags
	bool sair; //par fecahr o estado
	bool cooperativo; //para iniciar o modo de 2 jogadores
	bool ganhou;
	bool pausado;

	//funcoes
	virtual void iniTeclas() = 0; // cada estado vai definir a utilizacao das teclas

	

public:
	//construtora/destrutora
	Estado(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados, bool cooperativo);
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
	virtual void atualiza(const float& td) = 0;
	virtual void renderiza(sf::RenderTarget* target = NULL) = 0;
	virtual void atualizaTecla(const float& td);



};

