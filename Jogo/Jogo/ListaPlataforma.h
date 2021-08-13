#pragma once
#include <list>
#include "Plataforma.h"
using namespace std;

class ListaPlataforma
{
private:
	/*Variaveis*/
	list<Plataforma*> listaPlataforma;
	int n_elementos;

public:
	/*Construtora e destrutora*/
	ListaPlataforma();
	~ListaPlataforma();

	/*funcoes*/
	void inserir(Plataforma* plataforma);
	Plataforma* getObjeto(int i);
	int getNumElemento();

};

