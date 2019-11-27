#ifndef _DMG_ENTITY_
#define _DMG_ENTITY_

//#include "Entity.h"
#include <map>
#include "Entity.h"
//using namespace pl;
class DamageableEntity : public Entity {
public:
	DamageableEntity();
	DamageableEntity(Vector2 pos);
	~DamageableEntity();
private:


	//OnCollision, onCollisionHitbox

	//damagetaken
	//OnDamageTaken
	/*
	virtual bool isAtFullHealth();
	virtual bool isAtHalfHealth();
	virtual bool isAtCriticalHealth();
	virtual bool isAtLethalHealth();
	virtual bool isShadowDamaged();
	virtual bool isDamaged();


	virtual void OnDamageTaken();
	virtual void OnShadowDamageTaken();
	virtual void OnShadowDamageRecoveryStart();
	virtual void OnShadowDamageFullRecovery();
	*/


	float mHealthCriticalThreshold;
	//Health
	float mCurrentHealth;
	float mMaxHealth;
	std::map<Entity*, float> mShadowDamageTracker;//The shadow dmage
	//float mShadowDamage;



	int mSDRecoveryTimer;//When timer <= 0, recovery starts
	int mSDRecoveryTime;
	float mSDRecoveryRate;
};

#endif // !_DMG_ENTITY_
