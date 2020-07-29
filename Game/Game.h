#pragma once
#include <core.h>
#include "Math/MathFile.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Actor.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Object/Scene.h"
#include <list>
#include <string>
#include <iostream>
#include <vector>


class Game
{
public:
	enum class eState
	{
		INIT,
		TITLE,
		START_GAME,
		PLAYER_DEAD,
		GAME_WAIT,
		GAME,
		GAME_OVER
	};

public:
	void Startup();
	void Shutdown();

	bool Update(float dt);
	void Draw(Core::Graphics& graphics);

	void AddScore(int score) { m_score += score; }
	void SetState(eState state) { m_state = state; }

	void CreatePickup();

protected:
	eState m_state{ eState::TITLE };
	int m_lives{ 3 };
	int m_score{ 0 };

	Scene m_scene;

	float m_frameTime;
	float m_spawnTime{ 0 };
	float m_stateTime{ 0 };

public:
	static const int WIDTH, HEIGHT;
};