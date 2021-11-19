#pragma once
#include"EntidadeDinamica.h"

class AIOption
{
protected:

	EntidadeDinamica& self;
	EntidadeDinamica& entity;

public:
	AIOption(EntidadeDinamica& self, EntidadeDinamica& entity)
		: self(self), entity(entity)
	{

	}

	virtual void update(const float& dt) = 0;
};