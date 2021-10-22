#include "Fase1.h"
using namespace std;

Fase1::Fase1():EstadoFase(teclasDisponiveis, janela, estados)
{
	errno_t erro;
	if(erro = fopen_s(&fase, "fases/fase1.txt", "r"))
		cout<< "Arquivo nao abriu" << endl;
	gerarFase();

}

Fase1::~Fase1()
{
}
