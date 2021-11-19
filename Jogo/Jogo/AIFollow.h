#pragma once
#include "AIOption.h"
class AIFollow :
    public AIOption
{
private:

public:
    AIFollow(EntidadeDinamica& self, EntidadeDinamica& entity);
    ~AIFollow();

    void update(const float& dt);
};
