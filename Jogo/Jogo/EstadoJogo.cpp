#include "EstadoJogo.h"
//funcao privada
void EstadoJogo::iniTeclas()
{
	this->teclas.emplace("MOVER_ESQ",this->teclasDisponiveis->at("A"));
	this->teclas.emplace("MOVER_DIR", this->teclasDisponiveis->at("D"));
	this->teclas.emplace("MOVER_CIMA", this->teclasDisponiveis->at("W"));
	this->teclas.emplace("MOVER_BAIXO", this->teclasDisponiveis->at("S"));
}

//construtora / destrutora
EstadoJogo::EstadoJogo(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela)
	:Estado(teclasDisponiveis, janela, estados, cooperativo)
{
	this->iniTeclas();
	jogador = new EntidadeDinamica();
	
}

EstadoJogo::~EstadoJogo()
{
	delete jogador;
}


//funcoes
void EstadoJogo::fechaEstado()
{
}

void EstadoJogo::atualiza(const float td)
{
	this->atualizaTeclas(td);
	//this->jogador.atualiza(td);
}

void EstadoJogo::renderiza(sf::RenderTarget* alvo)
{
	//alvo esta como poonteiro nulo
	if (!alvo)
	{
		alvo = this->janela;
	}
	this->jogador->renderiza(*alvo);

}

void EstadoJogo::atualizaTeclas(const float td)
{
	//atualiza entrada do jogador
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("MOVE_ESQ"))))
		this->jogador->move(td, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("MOVE_CIMA"))))
		this->jogador->move(td, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("MOVE_BAIXO"))))
		this->jogador->move(td, 0.f, 1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("MOVE_DIR"))))
		this->jogador->move(td, 1.f, 0.f);
}
