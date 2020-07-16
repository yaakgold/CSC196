#pragma once
#include "Actor.h"
#include <core.h>
#include <vector>
#include <list>

namespace hummus
{
	class Scene
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void AddActor(class Actor* actor);
		void RemoveActor(class Actor* object);

		template<typename T>
		Actor* GetActor() 
		{
			Actor* result{ nullptr };
			for (Actor* actor : m_actors)
			{
				result = dynamic_cast<T*>(actor);
				if (result) break;
			}

			return result;
		}

		template <typename T>
		std::vector<T*> GetActors() 
		{
			std::vector<Actor*> results;
			for (Actor* actor : m_actors)
			{
				T* result = dynamic_cast<T*>(actor);
				if (result) results.push_back(result);
			}

			return results;			
		}

	private:
		std::list<class Actor*> m_actors;
	};
}