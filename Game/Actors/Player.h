#pragma once
#include "Pickups.h"
#include <Object\Actor.h>

using namespace hummus;

class Player : public Actor
{
public:
	virtual eType GetType() { return eType::PLAYER; }

	virtual bool Load(const std::string& fileName) override;

	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* collision);

	void DeactivatePickup();
	void ActivatePickup(Pickups::ePickup newPickup);
	std::string GetPickup();
	float GetPickupTimeLeft();

protected:
	float thrust;
	float fireRate{ 0.4f };
	float fireTimer{ 0.0f };

	float pickupTime{ 5.0f };
	float timeWithPickup{ 0.0f };

	Vector2 velocity;
	float maxSpeed{ 400 };
	float rotSpeed;

	Pickups::ePickup currentUpgrade;
	float scaleMult{ 1 };
	int numBullets{ 1 };
};
