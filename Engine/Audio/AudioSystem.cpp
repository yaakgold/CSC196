#include "pch.h"
#include "AudioSystem.h"

hummus::AudioSystem g_audioSystem;

namespace hummus
{
	void hummus::AudioSystem::Startup()
	{
		FMOD::System_Create(&m_system);

		void* extraDriverData = nullptr;
		m_system->init(32, FMOD_INIT_NORMAL, extraDriverData);
	}

	void hummus::AudioSystem::Shutdown()
	{
		for (auto& sound : m_sounds)
		{
			sound.second->release();
		}
		m_sounds.clear();

		m_system->close();
		m_system->release();
	}

	void hummus::AudioSystem::Update(float dt)
	{
		m_system->update();
	}

	void hummus::AudioSystem::AddAudio(const std::string& name, const std::string& fileName)
	{
		if (m_sounds.find(name) == m_sounds.end())
		{
			FMOD::Sound* sound{ nullptr };
			m_system->createSound(fileName.c_str(), FMOD_DEFAULT, 0, &sound); 
			m_sounds[name] = sound;
		}
	}

	void hummus::AudioSystem::PlayAudio(const std::string& name)
	{
		auto iter = m_sounds.find(name);
		if (iter != m_sounds.end())
		{
			FMOD::Sound* sound = iter->second;
			sound->setMode(FMOD_LOOP_OFF);
			FMOD::Channel* channel;
			m_system->playSound(sound, 0, false, &channel);
		}
	}
}