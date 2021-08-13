#include"EstadoFase1.h"
#include"Botao.h"
#include"UIManager.h"

class EstadoMenuPrincipal :
	public Estado
{
private:
	/*Variaveis*/
	sf::Texture texturaPlanoDeFundo;
	sf::RectangleShape planoDeFundo;
	std::map<std::string, Botao*> botoes;

	/*Funçõees inicializadoras*/
	void initVariaveis();
	void initPlanoDeFundo();
	void iniTeclas();
	void iniBotoes();

protected:
	sf::Sprite sprite;

public:
	/*Construtora e destrutora*/
	EstadoMenuPrincipal(std::map<std::string, int>* teclasDisponiveis, sf::RenderWindow* janela, std::stack<Estado*>* estados);// , UIManager* ui_manager);
	virtual ~EstadoMenuPrincipal();

	/*Funções*/
	void atualizaTeclas(const float td);
	void atualiza(const float& td) override; //chama atualizaTecla
	void renderiza(sf::RenderTarget* alvo = NULL);
	void atualizaBotoes();
	void renderizaBotoes(sf::RenderTarget* alvo = NULL);
};
