#ifndef __Collider__
#define __Collider__
//#include "Vector2.h"
#include "SFML/Graphics.hpp"


class Collider
{
public:
	Collider();
	virtual ~Collider();

	virtual bool Collide(const Collider& collider);
	virtual bool Collide(sf::Vector2f& point);
	virtual bool Collide(sf::Vector2f& from, sf::Vector2f& to);



	//virtual Collider Clone();




};
/*
class Hitbox {
public:
	Hitbox(float with, float height, float x, float y);
	Hitbox(const Hitbox& h);
	virtual Collider Clone();

	virtual bool Collide(const Hitbox& hitbox);
	virtual bool Collide(const sf::Vector2f& point);
	
	virtual void Render(void* renderTarget);

};
*/

#endif // !__Collider__

