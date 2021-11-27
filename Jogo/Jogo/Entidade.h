#pragma once
#include"ComponenteHitbox.h"
#include"ComponenteAtributos.h"

class Entidade
{
private:
	void initVariaveis();

protected:
	ComponenteHitbox* componenteHitbox;

	/*Variaveis*/
	sf::RectangleShape corpo; /*area a ser afetada pela colisao*/
	sf::Sprite sprite;

public:
	/*Construtora e destrutora*/
	Entidade();
	virtual ~Entidade();

	virtual const sf::Vector2f& getPosition() const;

	/*Funções de Componente*/
	void createHitboxComponent(sf::Sprite& sprite, 
		const float offset_x, const float offset_y, 
		float width, float height);

	/*Funções*/
	void setTexture(sf::Texture& texture);
	virtual void setPosition(const float x, const float y);
	virtual void renderiza(sf::RenderTarget& alvo);
};
