#include "pch.h"
#include "Scene.h"
#include "Actor.h"

void hummus::Scene::Startup()
{
	//Nothing
}

void hummus::Scene::Shutdown()
{
	for (Actor* actor : m_actors)
	{
		auto iter = std::find(m_actors.begin(), m_actors.end(), actor);
		delete* iter;
	}

	m_actors.clear();
}

void hummus::Scene::Update(float dt)
{
	for (Actor* actor : m_actors)
	{
		actor->Update(dt);
	}
}

void hummus::Scene::Draw(Core::Graphics& graphics)
{
	for (Actor* actor : m_actors)
	{
		actor->Draw(graphics);
	}
}

void hummus::Scene::AddActor(Actor* actor)
{
	m_actors.push_back(actor);
}

void hummus::Scene::RemoveActor(Actor* object)
{
	auto iter = std::find(m_actors.begin(), m_actors.end(), object);
	if(iter != m_actors.end())
	{
		delete* iter;
		m_actors.erase(iter);
	}
}
