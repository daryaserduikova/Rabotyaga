#pragma once
#include <SFML/Audio.hpp>
#include <string>

namespace ApplesGame
{
    class AudioManager
    {
    public:
        ~AudioManager();

        bool Init(const std::string& resourcesPath);

        void PlayMusic();
        void PauseMusic();
        void StopMusic();

        void PlayEatApple();

        void SetMusicVolume(float volume01);
        void SetSfxVolume(float volume01);

        bool IsMusicPlaying() const;

        void Shutdown();

    private:
        sf::Music m_backgroundMusic;

        sf::SoundBuffer m_eatAppleBuffer;
        sf::Sound m_eatAppleSound;

        float m_musicVolume01 = 0.30F;
        float m_sfxVolume01 = 0.60F;

        static constexpr float k_MaxMusicVolume = 25.0F;
        static constexpr float k_MaxSfxVolume = 35.0F;
    };
}
