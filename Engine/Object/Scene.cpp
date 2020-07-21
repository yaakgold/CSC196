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
	//Check for collisions
	std::vector<Actor*> actors{ m_actors.begin(), m_actors.end() };
	for (size_t i = 0; i < actors.size(); i++)
	{
		for (size_t j = i + 1; j < actors.size(); j++)
		{
			float dist = Vector2::Distance(actors[i]->GetTransform().position, actors[j]->GetTransform().position);

			if (dist <= 10)//Collision
			{
				actors[i]->OnCollision(actors[j]);
				actors[j]->OnCollision(actors[i]);
			}
		}
	}

	//Remove destroyed actors
	auto iter = m_actors.begin();
	while (iter != m_actors.end())
	{
		if ((*iter)->GetDestroy())
		{
			delete* iter;
			iter = m_actors.erase(iter);
		}
		else
		{
			iter++;
		}
	}


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
	actor->SetScene(this);
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
