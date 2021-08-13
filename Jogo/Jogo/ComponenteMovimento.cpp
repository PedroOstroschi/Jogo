#include "ComponenteMovimento.h"

/*Funcoes Inicializadoras*/


/*Construtora e Destrutora*/
ComponenteMovimento::ComponenteMovimento(sf::Sprite& sprite, 
	float velocidadeMaxima, float aceleracao, float desaceleracao)
	: sprite(sprite),
	velocidadeMaxima(velocidadeMaxima), aceleracao(aceleracao), desaceleracao(desaceleracao)
{
	this->gravidade = 4.f;
	this->velocidadeMaximaY = 15.f;
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

	/*Aplica gravidade*/

	//this->velocidade.y += 1.0 * this->gravidade;
	//Verificar velocidade maxima
	if (this->velocidade.y > this->velocidadeMaximaY)
		this->velocidade.y = this->velocidadeMaximaY * ((this->velocidade.y < 0.f)? -1.f : 1.f);

	/*Acelera a sprite at� a velocidade maxima e ao parar de andar, a desacelera
	criando assim uma movimentacao mais fluida*/

	//X
	if (this->velocidade.x > 0.f)	//verifica se x eh positivo
	{
		//Verificar velocidade maxima
		if (this->velocidade.x > this->velocidadeMaxima)
			this->velocidade.x = this->velocidadeMaxima;

		//desaceleracao
		this->velocidade.x -= desaceleracao;
		if (this->velocidade.x < 0.f)
			this->velocidade.x = 0.f;
	}
	else if(this->velocidade.x < 0.f)	//verifica se x eh negativo
	{
		//Verificar velocidade maxima
		if (this->velocidade.x < -this->velocidadeMaxima)
			this->velocidade.x = -this->velocidadeMaxima;

		//desaceleracao
		this->velocidade.x += desaceleracao;
		if (this->velocidade.x > 0.f)
			this->velocidade.x = 0.f;
	}

	//Y
	if (this->velocidade.y > 0.f)	//check for positive y
	{
		//Verificar velocidade maxima
		if (this->velocidade.y > this->velocidadeMaxima)
			this->velocidade.y = this->velocidadeMaxima;

		//desaceleracao
		this->velocidade.y -= desaceleracao;
		if (this->velocidade.y < 0.f)
			this->velocidade.y = 0.f;
	}
	else if (this->velocidade.y < 0.f)	//check for negative y
	{
		//Verificar velocidade maxima
		if (this->velocidade.y < -this->velocidadeMaxima)
			this->velocidade.y = -this->velocidadeMaxima;

		//desaceleracao
		this->velocidade.y += desaceleracao;
		if (this->velocidade.y > 0.f)
			this->velocidade.y = 0.f;
	}

	//Movimentacao Final
	this->sprite.move(this->velocidade * td);	//usa velocidade
}