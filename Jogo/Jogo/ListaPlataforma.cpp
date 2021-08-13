#include "ListaPlataforma.h"

ListaPlataforma::ListaPlataforma()
{
	n_elementos = 0;
}

ListaPlataforma::~ListaPlataforma()
{
	listaPlataforma.clear();
	n_elementos = 0;
}

void ListaPlataforma::inserir(Plataforma* plataforma)
{
	listaPlataforma.push_back(plataforma);
	n_elementos++;
}

Plataforma* ListaPlataforma::getObjeto(int i)
{
	auto comeco = listaPlataforma.begin();
	advance(comeco, i);
	return (*comeco);
}

int ListaPlataforma::getNumElemento()
{
	return n_elementos;
}
