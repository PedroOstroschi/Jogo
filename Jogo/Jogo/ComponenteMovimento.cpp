#include "ComponenteMovimento.h"

/*Funcoes Inicializadoras*/


/*Construtora e Destrutora*/
ComponenteMovimento::ComponenteMovimento(sf::Sprite& sprite, 
	float velocidadeMaxima, float aceleracao, float desaceleracao)
	: sprite(sprite),
	velocidadeMaxima(velocidadeMaxima), aceleracao(aceleracao), desaceleracao(desaceleracao)
{
	
}

ComponenteMovimento::~ComponenteMovimento()
{

}

const sf::Vector2f& ComponenteMovimento::getVelocity() const
{
	return this->velocidade;
}

/*Funcoes*/
void ComponenteMovimento::move(const float dir_x, const float dir_y, const float& td)
{
	/*Acelerar sprite ate a velocidade maxima*/

	//Aceleracao
	this->velocidade.x += this->aceleracao * dir_x;

	this->velocidade.y += this->aceleracao * dir_y;

}

void ComponenteMovimento::update(const float& td)
{
	/*Acelera a sprite até a velocidade maxima e ao parar de andar, a desacelera
	criando assim uma movimentacao mais fluida*/

	//X
	if (this->velocidade.x > 0.f)	//check for positive x
	{
		//max velocity check
		if (this->velocidade.x > this->velocidadeMaxima)
			this->velocidade.x = this->velocidadeMaxima;

		//desaceleracao
		this->velocidade.x -= desaceleracao;
		if (this->velocidade.x < 0.f)
			this->velocidade.x = 0.f;
	}
	else if(this->velocidade.x < 0.f)	//check for negative x
	{
		//max vel check
		if (this->velocidade.x < -this->velocidadeMaxima)
			this->velocidade.x = -this->velocidadeMaxima;

		//deceleration
		this->velocidade.x += desaceleracao;
		if (this->velocidade.x > 0.f)
			this->velocidade.x = 0.f;
	}

	//Y
	if (this->velocidade.y > 0.f)	//check for positive y
	{
		//max velocity check
		if (this->velocidade.y > this->velocidadeMaxima)
			this->velocidade.y = this->velocidadeMaxima;

		//desaceleracao
		this->velocidade.y -= desaceleracao;
		if (this->velocidade.y < 0.f)
			this->velocidade.y = 0.f;
	}
	else if (this->velocidade.y < 0.f)	//check for negative y
	{
		//max vel check
		if (this->velocidade.y < -this->velocidadeMaxima)
			this->velocidade.y = -this->velocidadeMaxima;

		//deceleration
		this->velocidade.y += desaceleracao;
		if (this->velocidade.y > 0.f)
			this->velocidade.y = 0.f;
	}

	//Movimentacao Final
	this->sprite.move(this->velocidade * td);	//usa velocidade
}
