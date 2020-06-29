#include "DamagableEntity.h"

DamageableEntity::DamageableEntity():
	DamageableEntity(Vector2(0.0f, 0.0f))
{
}

DamageableEntity::DamageableEntity(Vector2 pos):
	Entity(pos)
{
}

DamageableEntity::~DamageableEntity()
{
}
