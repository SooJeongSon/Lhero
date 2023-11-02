#include "Breed.h"
#include "Mob.h"

Mob* Breed::CreateMob(float maxHp)
{
	return new Mob(*this, maxHp);
}
