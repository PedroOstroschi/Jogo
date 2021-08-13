#pragma once
#include "Elemento.h"

template <class TL>class Lista
{
private:
	/*variaveis*/
	Elemento<TL>* pPrimeiro;
	Elemento<TL>* pUltimo;
	int tamanho;

public:
	/*Construtora e destrutora*/
	Lista();
	~Lista();

	/*set e get*/
	const int getTamanho() { this->tamanho; }
	TL* getItem(int posicao)
	{
		Elemento<TL>* temporario = pPrimeiro;
		if (posicao == 0) { return temporario->getItem(); }
		for (int i = 0; i < posicao; i++)
		{
			temporario = temporario->getPProximo();
		}
		return temporario->getItem();
	}


	/*funcoes*/
	void push(TL* item)
	{
		if (pPrimeiro == nullptr)
		{
			pPrimeiro = new Elemento<TL>;
			pPrimeiro->setItem(item);
			pUltimo = pPrimeiro;
		}
		else
		{
			Elemento<TL>* temporario = new Elemento<TL>;
			temporario->setItem(item);
			pUltimo->setPPRoximo(temporario);
			pUltimo = temporario;
		}
		tamanho++;
	}

	void pop(TL* item)
	{
		Elemento<TL>* temporario = pPrimeiro;
		Elemento<TL>* temporarioAnterior = nullptr;

		while (temporario->getItem() != item)
		{
			temporarioAnterior = temporario;
			temporario = temporario->getPProximo();
		}
		if (temporario == pPrimeiro)
		{
			pPrimeiro = temporario->getPProximo();
		}
		else if(temporario == pUltimo)
		{
			temporarioAnterior->setPPRoximo(nullptr); /*deixa o ultimo elemento como nulo antes de passar o anteriror dele como novo ultimo*/
			pUltimo = temporarioAnterior;
		}
		else
		{
			temporarioAnterior->setPPRoximo(temporario->getPProximo());
		}
		delete temporario;
		tamanho--;
	}
};

/*Construtora e destrutora*/
template<class TL>
inline Lista<TL>::Lista()
{
	pPrimeiro = nullptr;
	pUltimo = nullptr;
	tamanho = 0;
}

template<class TL>
inline Lista<TL>::~Lista()
{
}
