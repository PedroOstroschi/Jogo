#include "stdafx.h"
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

void EstadoFase::iniFontes()
{
	if (!this->font.loadFromFile("Fonts/comic.ttf"))
	{
		throw("nao carregou fonte");
	}
}

void EstadoFase::iniTexturas()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Players/Player_1/player_1_sheet.png"))
	{
		throw "ERRO::ESTADO_JOGO::NAO_CARREGOU_TEXTURA_PLAYER";
	}
}

void EstadoFase::initPauseMenu()
{
	this->menupause = new MenuPause(this->janela, this->font);

	this->menupause->addButton("DESPAUSAR", 600.f, "DESPAUSAR");
	this->menupause->addButton("SALVAR", 700.f, "SALVAR");
	this->menupause->addButton("SAIR", 800.f, "SAIR");
}

void EstadoFase::iniJogadores()
{
	this->jogador = new Jogador(0, 0, this->textures["PLAYER_SHEET"]);
}

void EstadoFase::iniTileMap()
{
	this->tileMap = new TileMap(this->dataEstado->gridSize, 10, 10);
}

/*Construtora e Destrutora*/
EstadoFase::EstadoFase(DataEstado* data_estado)
	:Estado(data_estado)
{

	this->iniTeclas();
	this->iniFontes();
	this->iniTexturas();
	this->initPauseMenu();

	this->iniJogadores();
	this->iniTileMap();
	this->iniElementos();
}

EstadoFase::~EstadoFase()
{
	delete this->jogador;
	delete this->menupause;
	delete this->tileMap;
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

void EstadoFase::updatePlayerInput(const float td)
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

		
}

void EstadoFase::updatePauseMenuButtons()
{
	if (this->menupause->isButtonPressed("SAIR"))
		this->estados->top()->fechaEstado();

	if (this->menupause->isButtonPressed("DESPAUSAR"))
		this->estados->top()->despausaEstado();

	if (this->menupause->isButtonPressed("SALVAR"))
		this->estados->top()->salva();

}

void EstadoFase::atualiza(const float& td)
{
	this->atualizaPosicaoMouse();
	this->updateKeyTime(td);
	this->updateInput(td);

	if (!this->pausado)	//atualiza o jogo despausado
	{
		this->updatePlayerInput(td);

		this->jogador->atualiza(td);
	}
	else	//atualiza o menu de pausa
	{
		this->menupause->atualiza(this->mousePosView);

		this->updatePauseMenuButtons();
	}
}

void EstadoFase::renderiza(sf::RenderTarget* alvo)
{
	//alvo esta como poonteiro nulo
	if (alvo == NULL)
		alvo = this->janela;

	//this->map.render(*alvo);

	this->jogador->renderiza(*janela);

	if (this->pausado)	//render menu pause
	{
		this->menupause->renderiza(*alvo);
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

void EstadoFase::updateInput(const float& td)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("PAUSAR"))) && this->getKeytime())
	{
		if (!this->pausado)
			this->pausaEstado();
		else
			this->despausaEstado();
	}
}

void EstadoFase::salva()
{
}
