#include "stdafx.h"
#include "EstadoEditor.h"

/*Inicializadores*/
void EstadoEditor::initVariaveis()
{
	this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->dataEstado->gridSize), static_cast<int>(this->dataEstado->gridSize));
	this->colisao = false;
	this->tipo = TileTypes::DEFAULT;
}

void EstadoEditor::initPlanoDeFundo()
{

}

void EstadoEditor::iniTextos()
{

	this->cursorText.setFont(this->font);
	this->cursorText.setFillColor(sf::Color::Red);
	this->cursorText.setCharacterSize(24);
	this->cursorText.setPosition(this->mousePosView.x - 20.f, this->mousePosView.y - 90.f);

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

	this->menupause->addButton("DESPAUSAR", 500.f, "DESPAUSAR");
	this->menupause->addButton("CARREGAR", 600.f, "CARREGAR");
	this->menupause->addButton("SALVAR", 700.f, "SALVAR");
	this->menupause->addButton("SAIR", 800.f, "SAIR");
}

void EstadoEditor::iniBotoes()
{

}

void EstadoEditor::iniGui()
{
	this->sidebar.setSize(sf::Vector2f(24.f, static_cast<float>(this->dataEstado->gfxSettings->resolution.height)));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1.f);

	this->selectorRect.setSize(sf::Vector2f(this->dataEstado->gridSize, this->dataEstado->gridSize));
	
	this->selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setTextureRect(this->textureRect);

	this->textureSelector = new gui::TextureSelector(20.f, 20.f, 640.f, 640.f, 
		this->dataEstado->gridSize, this->tileMap->getTileSheet(),
		this->font, "X"
	);
}

void EstadoEditor::iniTileMap()
{
	this->tileMap = new TileMap(this->dataEstado->gridSize, 30, 17, "Resources/Images/Sprites/Map/mainlev_build.png");
}

/*Construtora e Destrutora*/
EstadoEditor::EstadoEditor(DataEstado* data_estado)
	: Estado(data_estado)
{
	//this->ui_manager = ui_manager;
	this->initVariaveis();
	this->initPlanoDeFundo();
	this->iniFontes();
	this->iniTextos();
	this->iniTeclas();
	this->initPauseMenu();
	this->iniBotoes();
	this->iniTileMap();
	this->iniGui();
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

	delete this->textureSelector;
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
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}
	}
	//remove tile
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeytime())
	{
		if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosWindow)))
		{
			if (!this->textureSelector->getActive())
				this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
		}
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

void EstadoEditor::updateGui(const float& td)
{
	this->textureSelector->update(this->mousePosWindow, td);

	if (!this->textureSelector->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition(this->mousePosGrid.x * this->dataEstado->gridSize, this->mousePosGrid.y * this->dataEstado->gridSize);

	}

	this->cursorText.setPosition(this->mousePosView.x - 30.f, this->mousePosView.y - 130.f);
	std::stringstream ss;

	ss << this->mousePosView.x << " " << this->mousePosView.y << 
		"\n" << this->mousePosGrid.x << " " << this->mousePosGrid.y <<
		"\n" << this->textureRect.left / 64 << " " << this->textureRect.top / 64;
	this->cursorText.setString(ss.str());
}

void EstadoEditor::updatePauseMenuBotoes()
{
	if (this->menupause->isButtonPressed("DESPAUSAR"))
		this->despausaEstado();
	if (this->menupause->isButtonPressed("SAIR"))
		this->fechaEstado();
	if (this->menupause->isButtonPressed("SALVAR"))
		this->tileMap->saveToFile("text_teste");
	if (this->menupause->isButtonPressed("CARREGAR"))
		this->tileMap->loadFromFile("text_teste");
}

void EstadoEditor::atualiza(const float& td)
{
	this->atualizaPosicaoMouse();
	this->updateKeyTime(td);
	this->atualizaTeclas(td);

	if (!this->pausado)	//despausado
	{
		this->atualizaBotoes();
		this->updateGui(td);
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
	if(!this->textureSelector->getActive())
		alvo.draw(this->selectorRect);

	this->textureSelector->render(alvo);

	alvo.draw(this->cursorText);

	alvo.draw(this->sidebar);
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

}
