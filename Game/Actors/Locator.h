#pragma once
#include <Object\Actor.h>

using namespace hummus;

class Locator : public Actor
{
public:
	Locator() = default;
	virtual ~Locator() {}

	virtual eType GetType() { return eType::LOCATOR; }

	virtual void Update(float dt) override;

};

