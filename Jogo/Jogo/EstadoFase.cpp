#include "EstadoFase.h"

/*Inicializadores*/
void EstadoFase::iniElementos()
{
	listaEntidades->LEs.push(jogador);
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
	if (!this->textures["PLAYER"].loadFromFile("Resources/Images/Sprites/Players/1Woodcutter/Woodcutter.png"))
	{
		throw "ERRO::ESTADO_JOGO::NAO_CARREGOU_TEXTURA_PLAYER";
	}
}

void EstadoFase::iniJogadores()
{
	this->jogador = new Jogador(0, 0, this->textures["PLAYER"]);
}

/*Construtora e Destrutora*/
EstadoFase::EstadoFase(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados)
	:Estado(teclasDisponiveis, janela, estados, cooperativo)
{
	this->iniTeclas();
	this->iniTexturas();
	this->iniJogadores();
	this->iniElementos();

	listaEntidades = new ListaEntidade;
}

EstadoFase::~EstadoFase()
{
	delete this->jogador;
}

/*Fun��es*/
void EstadoFase::fechaEstado()
{
	std::cout << "fechando estado!" << "\n";
}

void EstadoFase::pausaEstado()
{
	this->estados->push(new EstadoPausado(this->teclasDisponiveis, this->janela, this->estados));
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
		this->pausaEstado();
}

void EstadoFase::atualiza(const float& td)
{
	this->atualizaPosicaoMouse();
	this->atualizaTeclas(td);

	this->jogador->atualiza(td);
}

void EstadoFase::renderiza(sf::RenderTarget* alvo)
{
	//alvo esta como poonteiro nulo
	if (alvo == NULL)
	{
		alvo = this->janela;
	}

	this->jogador->renderiza(this->janela);
}

void EstadoFase::salva()
{
}