#include "EstadoEditor.h"

/*Inicializadores*/
void EstadoEditor::initVariaveis()
{

}

void EstadoEditor::initPlanoDeFundo()
{
}

void EstadoEditor::iniTeclas()
{
	std::ifstream ifs("Config/estado_editor_teclas.ini");

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

void EstadoEditor::iniBotoes()
{

}

/*Construtora e Destrutora*/
EstadoEditor::EstadoEditor(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados)// , UIManager* ui_manager)
	:Estado(teclasDisponiveis, janela, estados, cooperativo)
{
	//this->ui_manager = ui_manager;
	this->initVariaveis();
	this->initPlanoDeFundo();
	this->iniFontes();
	this->iniTeclas();
	this->iniBotoes();
}

EstadoEditor::~EstadoEditor()
{
	auto it = this->botoes.begin();
	for (it = this->botoes.begin(); it != this->botoes.end(); ++it)
	{
		delete it->second;
	}
}

/*Funções*/

void EstadoEditor::atualizaTeclas(const float td)
{
	//atualiza entrada do jogador
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
	{
		std::cout << "EDITOR" << "\n";
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("FECHAR"))))
		this->fechaEstado();
}

void EstadoEditor::atualiza(const float& td)
{
	this->atualizaTeclas(td);
	this->atualizaPosicaoMouse();
	this->atualizaBotoes();
}

void EstadoEditor::renderiza(sf::RenderTarget* alvo)
{
	//alvo esta como ponteiro nulo
	if (!alvo)
		alvo = this->janela;

	this->renderizaBotoes(*alvo);

}

void EstadoEditor::atualizaBotoes()
{
	/*atualiza todos os botoes desse estado e cuida das suas funcionalidades*/
	//main loop
	for (auto& it : this->botoes)
	{
		it.second->update(this->mousePosView);
	}

}

void EstadoEditor::renderizaBotoes(sf::RenderTarget& alvo)
{
	for (auto& it : this->botoes)
	{
		it.second->render(alvo);
	}
}