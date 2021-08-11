#pragma once
#include "Entidade.h"
#include "ComponenteMovimento.h"

class EntidadeDinamica :
	public Entidade
{
private:

protected:
	ComponenteMovimento* componenteMovimento;
public:
	/*Construtora e destrutora*/
	EntidadeDinamica();
	virtual~EntidadeDinamica();

	/*Componentes*/
	void createMovementComponent(const float velocidadeMaxima, const float aceleracao, const float desaceleracao);

	/*Funções*/
	virtual void move(const float dir_x, const float dir_y, const float& td);
	virtual void atualiza(const float td);
};
