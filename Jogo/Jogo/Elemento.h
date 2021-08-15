#pragma once
template<class TE>class Elemento /*TE, Template Elemento*/
{
private:
	/*variaveis*/
	Elemento<TE>* pProximo;
	TE* item;

public:
	/*contrutora destrutora*/
	Elemento();
	~Elemento();

	/*set e get*/
	void setPPRoximo(Elemento<TE>* pProximo) { this->pProximo = pProximo; }
	void setItem(TE* item) { this->item = item;  }
	Elemento<TE>* getPProximo() { return this->pProximo; }
	TE* getItem() { return this->item; }


};

template<class TE>
inline Elemento<TE>::Elemento()
{
	pProximo = nullptr;
	item = nullptr;
}

template<class TE>
inline Elemento<TE>::~Elemento()
{
	
}
