#include "EntidadeDinamica.h"

//Construtora / Destrutora 
EntidadeDinamica::EntidadeDinamica() :
	Entidade()
{
	this->velocidade = 100.f;
}

EntidadeDinamica::~EntidadeDinamica()
{
}



/*void EntidadeDinamica::atualiza(const float td)
{

}*/

void EntidadeDinamica::move(const float& td, const float dir_x, const float dir_y)
{
	this->forma.move(dir_x * this->velocidade * td, dir_y * this->velocidade * td);
}
