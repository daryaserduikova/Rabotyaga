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
        void Shutdown();

        void PlayMusic();
        void PauseMusic();
        void StopMusic();

        void PlayEatApple();

        void SetMusicVolume(float volume01);
        void SetSfxVolume(float volume01);

        bool IsMusicPlaying() const;

    private:
        static constexpr float k_MaxMusicVolume = 25.0F;
        static constexpr float k_MaxSfxVolume = 35.0F;

        sf::Music m_BackgroundMusic;

        sf::SoundBuffer m_EatAppleBuffer;
        sf::Sound m_EatAppleSound;

        float m_MusicVolume01 = 1.0F;
        float m_SfxVolume01 = 1.0F;
    };
}