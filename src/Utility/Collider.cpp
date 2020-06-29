#include "Collider.h"


Collider::Collider()
{
}


Collider::~Collider()
{
}

bool Collider::Collide(const Collider & collider)
{
	return false;
}

bool Collider::Collide(sf::Vector2f & point)
{
	return false;
}

bool Collider::Collide(sf::Vector2f & from, sf::Vector2f & to)
{
	return false;
}



