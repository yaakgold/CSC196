#pragma once

#include <fmod.hpp>
#include <string>
#include <map>

namespace hummus
{
	class AudioSystem
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);

		void AddAudio(const std::string& name, const std::string& fileName);
		void PlayAudio(const std::string& name);

	private:
		FMOD::System* m_system;
		std::map<std::string, FMOD::Sound*> m_sounds;
	};

}

extern hummus::AudioSystem g_audioSystem;