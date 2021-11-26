#include "stdafx.h"
#include "GUI.h"

/*Construtora e Destrutora*/
gui::Botao::Botao(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color corIdleT, sf::Color corHoverT, sf::Color corActiveT,
	sf::Color corIdle, sf::Color corHover, sf::Color corActive,
	sf::Color outlinecorIdle, sf::Color outlinecorHover, sf::Color outlinecorActive,
	short unsigned id)
{
	this->statusBotao = BTN_IDLE;
	this->id = id;

	this->box.setPosition(sf::Vector2f(x, y));
	this->box.setSize(sf::Vector2f(width, height));
	this->box.setFillColor(corIdle);
	this->box.setOutlineThickness(1.f);
	this->box.setOutlineColor(outlinecorIdle);

	this->font = font;
	this->texto.setFont(*this->font);
	this->texto.setString(text);
	this->texto.setFillColor(corIdleT);
	this->texto.setCharacterSize(character_size);
	this->texto.setPosition(
		this->box.getPosition().x + (this->box.getGlobalBounds().width / 2.f) - this->texto.getGlobalBounds().width / 2.f,
		this->box.getPosition().y + (this->box.getGlobalBounds().height / 2.f) - this->texto.getGlobalBounds().height / 2.f
	);
	
	this->corIdleT = corIdleT;
	this->corHoverT = corHoverT;
	this->corActiveT = corActiveT;

	this->corIdle = corIdle;
	this->corHover = corHover;
	this->corActive = corActive;

	this->outlinecorIdle = outlinecorIdle;
	this->outlinecorHover = outlinecorHover;
	this->outlinecorActive = outlinecorActive;

}

gui::Botao::~Botao()
{

}

/*Accessors*/
const bool gui::Botao::isPressed() const
{
	if (this->statusBotao == BTN_ACTIVE)
		return true;
	else
		return false;
}

const std::string gui::Botao::getText() const
{
	return this->texto.getString();
}

const short unsigned& gui::Botao::getId() const
{
	return this->id;
}

/*modifiers*/
void gui::Botao::setText(const std::string text)
{
	this->texto.setString(text);
}

void gui::Botao::setId(const short unsigned id)
{
	this->id = id;
}

/*Funções*/
void gui::Botao::update(const sf::Vector2f& mousePos)
{
	/*updeita os booleanos para ver se o mouse ta em cima ou pressionando o botao*/
	
	//inicia o botao em idle
	this->statusBotao = BTN_IDLE;
	//hover
	if (this->box.getGlobalBounds().contains(mousePos))
	{
		this->statusBotao = BTN_HOVER;

		//active
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->statusBotao = BTN_ACTIVE;
		}
	}

	switch (this->statusBotao)
	{
		case BTN_IDLE:
			this->box.setFillColor(this->corIdle);
			this->texto.setFillColor(this->corIdleT);
			this->box.setOutlineColor(this->outlinecorIdle);
			break;

		case BTN_HOVER:
			this->box.setFillColor(this->corHover);
			this->texto.setFillColor(this->corHoverT);
			this->box.setOutlineColor(this->outlinecorHover);
			break;

		case BTN_ACTIVE:
			this->box.setFillColor(this->corActive);
			this->texto.setFillColor(this->corActiveT);
			this->box.setOutlineColor(this->outlinecorActive);
			break;

		default:
			this->box.setFillColor(sf::Color::Red);
			this->texto.setFillColor(sf::Color::Blue);
			this->box.setOutlineColor(sf::Color::Green);
			break;

	}
}

void gui::Botao::render(sf::RenderTarget& alvo)
{
	alvo.draw(this->box);
	alvo.draw(this->texto);
}

/*-----------------DropDownList------------------*/

gui::DropDownList::DropDownList(float x, float y, float width, float height, 
	sf::Font& font, std::string list[], 
	unsigned nrOfElements, unsigned default_index)
	: font(font), showList(false), keytimeMax(1.f), keytime(0.f)
{
	this->activeElement = new gui::Botao(
		x, y, width, height,
		&this->font, list[default_index], 14,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 200), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50)
	);

	for (size_t i = 0; i < nrOfElements; i++)
	{
		this->list.push_back(
			new gui::Botao(
				x, y + ((i+1) * height), width, height,
				&this->font, list[i], 12,
				sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
				sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
				i
			)
		);
	}
}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}
}

const unsigned short& gui::DropDownList::getActiveElementdId() const
{
	return this->activeElement->getId();
}

//accessors
const bool gui::DropDownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

//functions
void gui::DropDownList::updateKeytime(const float& td)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * td;
}

void gui::DropDownList::update(const sf::Vector2f& mousePos, const float& td)
{
	this->updateKeytime(td);

	this->activeElement->update(mousePos);

	//mostra e esconde a lista
	if (this->activeElement->isPressed() && this->getKeytime())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->update(mousePos);

			if (i->isPressed() && this->getKeytime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget& alvo)
{
	this->activeElement->render(alvo);

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(alvo);
		}
	}
}

/*----------------TEXTURESELECTOR---------------------*/
gui::TextureSelector::TextureSelector(float x, float y, float width, float height,
	float gridSize, const sf::Texture* texture_sheet, 
	sf::Font& font, std::string text) 
	:	keytimeMax(1.f), keytime(0.f)
{
	this->gridSize = gridSize;
	this->active = false;
	this->hidden = false;
	float offset = 60.f;


	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x + offset, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->bounds.getGlobalBounds().width, this->sheet.getGlobalBounds().height));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->bounds.getGlobalBounds().height, this->sheet.getGlobalBounds().width));
	}

	this->selector.setPosition(x + offset, y);
	this->selector.setSize(sf::Vector2f(gridSize, gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(2.f);
	this->selector.setOutlineColor(sf::Color::Red);

	this->textureRect.width = static_cast<int>(gridSize);
	this->textureRect.height = static_cast<int>(gridSize);

	this->minimizar = new gui::Botao(
		x, y, 50.f, 50.f,
		&font, text, 30,
		sf::Color(sf::Color::White), sf::Color(sf::Color::Red), sf::Color(sf::Color::Yellow),
		sf::Color(sf::Color::Transparent), sf::Color(sf::Color::Transparent), sf::Color(sf::Color::Transparent));;

}

gui::TextureSelector::~TextureSelector()
{
	delete this->minimizar;
}


//ACCESSORS
const bool& gui::TextureSelector::getActive() const
{
	return this->active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

const bool gui::TextureSelector::getKeyTime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

//FUNCOES
void gui::TextureSelector::updateKeytime(const float& td)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * td;
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& td)
{
	this->updateKeytime(td);

	this->minimizar->update(static_cast<sf::Vector2f>(mousePosWindow));

	if (this->minimizar->isPressed() && this->getKeyTime())
	{
		if (this->hidden)
			this->hidden = false;
		else
			this->hidden = true;
	}

	if (!this->hidden)
	{
		if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
			this->active = true;
		else 
			this->active = false;

		if (this->active)
		{
			this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
			this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);
		
			this->selector.setPosition(
				this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
			);

			//update texture rectangle
			this->textureRect.left = static_cast<int>(this->selector.getPosition().x -  this->bounds.getPosition().x);
			this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
}

void gui::TextureSelector::render(sf::RenderTarget& alvo)
{
	if (!this->hidden)
	{
		alvo.draw(this->bounds);
		alvo.draw(this->sheet);

		if(this->active)
			alvo.draw(this->selector);
	}

	this->minimizar->render(alvo);
}
