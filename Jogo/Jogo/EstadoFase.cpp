#include "EstadoFase.h"

/*Inicializadores*/
void EstadoFase::iniElementos()
{

}

void EstadoFase::iniTeclas()
{
	std::ifstream ifs("Config/estado_jogo_teclas.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->teclas[key] = this->teclasDisponiveis->at(key2);
		}
	}

	ifs.close();
}

void EstadoFase::iniTexturas()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Players/Player_1/player_1_sheet.png"))
	{
		throw "ERRO::ESTADO_JOGO::NAO_CARREGOU_TEXTURA_PLAYER";
	}
}

void EstadoFase::iniJogadores()
{
	this->jogador = new Jogador(0, 0, this->textures["PLAYER_SHEET"]);
}

/*Construtora e Destrutora*/
EstadoFase::EstadoFase(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados)
	:Estado(teclasDisponiveis, janela, estados, cooperativo), menupause(janela, estados)
{

	this->iniTeclas();
	this->iniTexturas();
	this->iniJogadores();
	this->iniElementos();

}

EstadoFase::~EstadoFase()
{
	delete this->jogador;
}

/*Funções*/
void EstadoFase::fechaEstado()
{
	std::cout << "fechando estado!" << "\n";
}

void EstadoFase::pausaEstado()
{
	this->pausado = true;
	//this->estados->push(new EstadoPausado(this->teclasDisponiveis, this->janela, this->estados));
}

void EstadoFase::despausaEstado()
{
	this->pausado = false;
}

void EstadoFase::atualizaTeclas(const float td)
{
	//atualiza entrada do jogador
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("MOVE_ESQ"))))
		this->jogador->move(-1.f, 0.f, td);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("MOVE_CIMA"))))
		this->jogador->move(0.f, -1.f, td);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("MOVE_BAIXO"))))
		this->jogador->move(0.f, 1.f, td);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("MOVE_DIR"))))
		this->jogador->move(1.f, 0.f, td);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("FECHAR"))))
		this->sair = true;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("PAUSAR"))))
	{
		if (!this->pausado)
			this->pausaEstado();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("DESPAUSAR"))))
	{
		if (this->pausado)
			this->despausaEstado();
	}
		
}

void EstadoFase::atualiza(const float& td)
{
	if (!this->pausado)	//atualiza o jogo despausado
	{
		this->atualizaPosicaoMouse();
		this->atualizaTeclas(td);

		this->jogador->atualiza(td);
	}
	else	//atualiza o menu de pausa
	{
		this->menupause.atualiza();
	}
}

void EstadoFase::renderiza(sf::RenderTarget* alvo)
{
	//alvo esta como poonteiro nulo
	if (alvo == NULL)
		alvo = this->janela;

	this->jogador->renderiza(*janela);

	if (this->pausado)	//render menu pause
	{
		this->menupause.renderiza(alvo);
	}
}

/*criacao da fase*/

void EstadoFase::gerarFase()
{
//
}

void EstadoFase::gerarInimigos() {

}

void EstadoFase::gerarObstaculos()
{
}

void EstadoFase::salva()
{
}
