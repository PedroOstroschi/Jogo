#include "stdafx.h"
#include "ComponenteAnimacao.h"

ComponenteAnimacao::ComponenteAnimacao(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite), textureSheet(texture_sheet), lastAnimation(NULL), priorityAnimation(NULL)
{

}

ComponenteAnimacao::~ComponenteAnimacao()
{
	for (auto &i : this->animations)
	{
		delete i.second;
	}
}



//acess
const bool& ComponenteAnimacao::isDone(const std::string key)
{
	return this->animations[key]->isDone();
}

//funcoes
void ComponenteAnimacao::addAnimation(
	const std::string key,
	float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
	this->animations[key] = new Animation(
		this->sprite, this->textureSheet,
		animation_timer,
		start_frame_x, start_frame_y, frames_x, frames_y, width, height
	);
}

const bool& ComponenteAnimacao::play(const std::string key, const float& dt, const bool priority)
{


	if (this->priorityAnimation) //se tiver animacao prioritaria
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//se a animacao prioritaria for feita, retira-la
			if (this->animations[key]->play(dt))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else //roda animacao se nao tiver prioritaria
	{
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if(this->lastAnimation != this->animations[key])
		{
			if(this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dt);
	}
	return this->animations[key]->isDone();
}

const bool& ComponenteAnimacao::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{
	if (this->priorityAnimation)
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//se a animacao prioritaria for feita, retira-la
			if (this->animations[key]->play(dt, abs(modifier / modifier_max)))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else
	{
		//se for prioridade,setar
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dt, abs(modifier / modifier_max));

	}
	return this->animations[key]->isDone();
}
