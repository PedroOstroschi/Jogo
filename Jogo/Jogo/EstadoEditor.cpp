#include "stdafx.h"
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

void EstadoEditor::initPauseMenu()
{
	this->menupause = new MenuPause(this->janela, this->font);

	this->menupause->addButton("DESPAUSAR", 600.f, "DESPAUSAR");
	this->menupause->addButton("SAIR", 800.f, "SAIR");
}

void EstadoEditor::iniBotoes()
{

}

void EstadoEditor::iniGui()
{
	this->selectorRect.setSize(sf::Vector2f(this->dataEstado->gridSize, this->dataEstado->gridSize));
	
	this->selectorRect.setFillColor(sf::Color::Transparent);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);
}

void EstadoEditor::iniTileMap()
{
	this->tileMap = new TileMap(this->dataEstado->gridSize, 10, 10);
}

/*Construtora e Destrutora*/
EstadoEditor::EstadoEditor(DataEstado* data_estado)
	: Estado(data_estado)
{
	//this->ui_manager = ui_manager;
	this->initVariaveis();
	this->initPlanoDeFundo();
	this->iniFontes();
	this->iniTeclas();
	this->initPauseMenu();
	this->iniBotoes();
	this->iniGui();
	this->iniTileMap();
}

EstadoEditor::~EstadoEditor()
{
	auto it = this->botoes.begin();
	for (it = this->botoes.begin(); it != this->botoes.end(); ++it)
	{
		delete it->second;
	}

	delete this->menupause;

	delete this->tileMap;
}

/*Funções*/

void EstadoEditor::atualizaTeclas(const float td)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->teclas.at("PAUSAR"))) && this->getKeytime())
	{
		if (!this->pausado)
			this->pausaEstado();
		else
			this->despausaEstado();
	}
}

void EstadoEditor::atualizaEditorInput(const float& td)
{
	//add tile
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeytime())
	{
		this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
	}
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

void EstadoEditor::updateGui()
{
	this->selectorRect.setPosition(this->mousePosGrid.x * this->dataEstado->gridSize, this->mousePosGrid.y * this->dataEstado->gridSize);
}

void EstadoEditor::updatePauseMenuBotoes()
{
	if (this->menupause->isButtonPressed("SAIR"))
		this->fechaEstado();
}

void EstadoEditor::atualiza(const float& td)
{
	this->atualizaPosicaoMouse();
	this->updateKeyTime(td);
	this->atualizaTeclas(td);

	if (!this->pausado)	//despausado
	{
		this->atualizaBotoes();
		this->updateGui();
		this->atualizaEditorInput(td);
	}
	else //pausado
	{
		this->menupause->atualiza(this->mousePosView);
		this->updatePauseMenuBotoes();
	}
}

void EstadoEditor::renderizaBotoes(sf::RenderTarget& alvo)
{
	for (auto& it : this->botoes)
	{
		it.second->render(alvo);
	}
}

void EstadoEditor::renderizaGui(sf::RenderTarget& alvo)
{
	alvo.draw(this->selectorRect);
}

void EstadoEditor::renderiza(sf::RenderTarget* alvo)
{
	//alvo esta como ponteiro nulo
	if (!alvo)
		alvo = this->janela;

	this->tileMap->render(*alvo);

	this->renderizaBotoes(*alvo);
	this->renderizaGui(*alvo);

	if (this->pausado)
	{
		this->menupause->renderiza(*alvo);
	}

	//REMOVE
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x + 10, this->mousePosView.y - 45);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(24);
	mouseText.setFillColor(sf::Color::Red);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	alvo->draw(mouseText);

}
