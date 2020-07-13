#pragma once
#include <Object\Actor.h>

using namespace hummus;

class Enemy : public Actor
{
public:
	virtual bool Load(const std::string& fileName) override;

	virtual void Update(float dt) override;

	void SetTarget(Actor* actor) { m_target = actor; }

protected:
	float m_thrust{ 0.0f };
	Actor* m_target{ nullptr };
	float speed{ 100.0f };
};
