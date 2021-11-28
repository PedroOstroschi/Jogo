#pragma once
#include "Entidade.h"
#include "ComponenteMovimento.h"
#include "ComponenteAnimacao.h"
#include "ComponenteHitbox.h"

class EntidadeDinamica :
	public Entidade
{
private:

protected:
	ComponenteMovimento* componenteMovimento;
	ComponenteAnimacao* componenteAnimacao;

public:
	void initVariaveis();

	/*Construtora e destrutora*/
	EntidadeDinamica();
	virtual~EntidadeDinamica();

	/*Cria Componentes*/
	void createMovementComponent(const float velocidadeMaxima, const float velocidadeMaximaY, const float aceleracao, const float desaceleracao);
	void createAnimationComponent(sf::Texture& texture_sheet);

	/*Accessors*/


	/*Modifiers*/

	/*Funções*/
	virtual void move(const float dir_x, const float dir_y, const float& td);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual const sf::FloatRect& getNextPositionBounds(const float& td) const;
	
	const sf::Vector2f& getSpritePosition() const;
	const sf::Vector2f getCenter() const;
	const sf::Vector2f getSpriteCenter() const;
	virtual void atualiza(const float & td);
};
