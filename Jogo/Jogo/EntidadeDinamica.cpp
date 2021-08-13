#include "EntidadeDinamica.h"

/*Construtora e Destrutora*/
EntidadeDinamica::EntidadeDinamica() :
	Entidade()
{
	//this->componenteMovimento = NULL;
}

EntidadeDinamica::~EntidadeDinamica()
{
	delete this->componenteMovimento;
}

/*Funcoes Componentes*/
void EntidadeDinamica::createMovementComponent(const float velocidadeMaxima, const float aceleracao, const float desaceleracao)
{
	this->componenteMovimento = new ComponenteMovimento(this->sprite, velocidadeMaxima, aceleracao, desaceleracao);
}

/*Funções*/
void EntidadeDinamica::atualiza(const float td)
{
	if (this->componenteMovimento)
		this->componenteMovimento->update(td);
}

void EntidadeDinamica::move(const float dir_x, const float dir_y, const float& td)
{
	if (this->componenteMovimento)
	{
		this->componenteMovimento->move(dir_x, dir_y, td);	//seta velocidade
	}
}