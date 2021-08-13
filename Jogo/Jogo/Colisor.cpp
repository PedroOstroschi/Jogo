#include "Colisor.h"


Colisor::Colisor(sf::Sprite& sprite, sf::RectangleShape& corpo):
	sprite(sprite), corpo(corpo)
{
}

Colisor::~Colisor()
{
}

bool Colisor::verificaColisao(Colisor& outroCorpo, sf::Vector2f& direcao, float repulsao)
{
	/*variaveis auxiliares para facilitar a clareza*/
	float tamanhoAtualX, tamanhoAtualY, tamanhouOutroX, tamanhouOutroY;
	tamanhoAtualX = this->corpo.getSize().x;
	tamanhoAtualY = this->corpo.getSize().y;
	tamanhouOutroX = outroCorpo.corpo.getSize().x;
	tamanhouOutroY = outroCorpo.corpo.getSize().y;

	sf::Vector2f posicaoOutroCorpo = outroCorpo.corpo.getPosition();
	sf::Vector2f meioTamanhoOutroCorpo = outroCorpo.getMetadeDoTamanho();

	sf::Vector2f posicaoAtual = corpo.getPosition();
	sf::Vector2f meioTamanhoCorpoAtual = getMetadeDoTamanho();

	
	float variacaoX = posicaoOutroCorpo.x - posicaoAtual.x + ((tamanhouOutroX - tamanhoAtualX) / 2 );
	float variacaoY = posicaoOutroCorpo.y - posicaoAtual.y + ((tamanhouOutroY - tamanhoAtualY) / 2);

	float interseccaoX = abs(variacaoX) - (meioTamanhoOutroCorpo.x - meioTamanhoCorpoAtual.x);
	float interseccaoY = abs(variacaoY) - (meioTamanhoOutroCorpo.y - meioTamanhoCorpoAtual.y);

	/*se ha interseccao, eles colidiram*/
	if (interseccaoX < 0.0f && interseccaoY < 0.0f) {
		repulsao = std::min(std::max(repulsao, 0.0f), 1.0f);

		if (interseccaoX > interseccaoY)
		{
			if (variacaoX > 0.0f)
			{
				move(interseccaoX * (1.0f - repulsao), 0.0f);
				outroCorpo.move(-interseccaoX * repulsao, 0.0f);

				direcao.x = 1.0f;
				direcao.y = 0.0f;
			}
			else
			{
				move(-interseccaoX * (1.0f - repulsao), 0.0f);
				outroCorpo.move(interseccaoX * repulsao, 0.0f);

				direcao.x = -1.0f;
				direcao.y = 0.0f;
			}
		}
		else
		{
			if (variacaoY > 0.0f)
			{
				move(0.0f, interseccaoY * (1.0f - repulsao));
				outroCorpo.move(0.0f, -interseccaoY * repulsao);

				variacaoX = 0.0f;
				variacaoY = 1.0f;
			}
			else
			{
				move(0.0f, -interseccaoY * (1.0f - repulsao));
				outroCorpo.move(0.0f, interseccaoY * repulsao);

				direcao.x = 0.0f;
				direcao.y = -1.0f;
			}
		}
		return true;
	}
	return false;
}


