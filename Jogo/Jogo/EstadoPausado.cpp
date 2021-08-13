#include "EstadoPausado.h"

/*inicializadoras*/
void EstadoPausado::initVariaveis()
{

}

void EstadoPausado::initPlanoDeFundo()
{
	this->planoDeFundo.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->janela->getSize().x),
			static_cast<float>(this->janela->getSize().y)
		)
	);

	if (!this->texturaPlanoDeFundo.loadFromFile("Resources/Images/Backgrounds/background_grafico.png"))
	{
		throw "ERRO::ESTADO_PAUSADO::FALHOU_CARREGAR_TEXTURA_BACKGROUND";
	}

	this->planoDeFundo.setTexture(&this->texturaPlanoDeFundo);

}

void EstadoPausado::iniTeclas()
{
	std::ifstream ifs("Config/estado_pausado_teclas.ini");

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

void EstadoPausado::iniBotoes()
{
	this->botoes["DESPAUSAR"] = new Botao(802, 700, 150, 50,
		&this->font, "Despausar", 24,
		sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

	this->botoes["Salvar"] = new Botao(970, 700, 150, 50,
		&this->font, "Salvar", 24,
		sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

	this->botoes["Menu_Principal"] = new Botao(802, 770, 150, 50,
		&this->font, "Menu Principal", 24,
		sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

	this->botoes["Sair"] = new Botao(970, 770, 150, 50,
		&this->font, "Sair", 24,
		sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33), sf::Color(33, 33, 33, 33),
		sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

}


/*Construtora Destrutora*/
EstadoPausado::EstadoPausado(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados)
	:Estado(teclasDisponiveis, janela, estados, cooperativo)
{
	this->initVariaveis();
	this->initPlanoDeFundo();
	this->iniFontes();
	this->iniTeclas();
	this->iniBotoes();

}

EstadoPausado::~EstadoPausado()
{
	auto it = this->botoes.begin();
	for (it = this->botoes.begin(); it != this->botoes.end(); ++it)
	{
		delete it->second;
	}
}

/*Funcoes*/
void EstadoPausado::despausa()
{
	this->estados->pop();
}

void EstadoPausado::atualizaTeclas(const float td)
{
	//atualiza entrada do jogador
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		std::cout << "asasa" << "\n";
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("FECHAR"))))
		this->fechaEstado();
}

void EstadoPausado::atualiza(const float& td)
{
	this->atualizaTeclas(td);
	this->atualizaPosicaoMouse();
	this->atualizaBotoes();
}

void EstadoPausado::renderiza(sf::RenderTarget* alvo)
{
	//alvo esta como ponteiro nulo
	if (alvo == NULL)
		alvo = this->janela;

	alvo->draw(this->planoDeFundo);

	this->renderizaBotoes(alvo);

	//REMOVE
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x + 10, this->mousePosView.y + 15);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(24);
	mouseText.setFillColor(sf::Color::Black);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	alvo->draw(mouseText);
}

void EstadoPausado::atualizaBotoes()
{
	/*atualiza todos os botoes desse estado e cuida das suas funcionalidades*/
	//main loop
	for (auto& it : this->botoes)
	{
		it.second->update(this->mousePosView);
	}

	//despausa
	if (this->botoes["DESPAUSAR"]->isPressed())
	{
		this->despausa();
	}

	//Salva o jogo
	if (this->botoes["SALVAR"]->isPressed())
	{
		/*TODO*/
	}

	//Volta ao menu inicial
	if (this->botoes["MENU_PRINCIPAL"]->isPressed())
	{
		/*TODO*/
	}

	//Sai do jogo
	if (this->botoes["SAIR"]->isPressed())
	{
		this->sair = true;
	}

}

void EstadoPausado::renderizaBotoes(sf::RenderTarget* alvo)
{
	for (auto& it : this->botoes)
	{
		it.second->render(alvo);
	}
}




