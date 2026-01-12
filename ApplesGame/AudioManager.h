#pragma once
#include <SFML/Audio.hpp>
#include <string>

namespace ApplesGame
{
    class AudioManager
    {
    public:
        bool Init(const std::string& resourcesPath);

        void PlayMusic();
        void PauseMusic();
        void StopMusic();

        void PlayEatApple();

        void SetMusicVolume(float volume01);
        void SetSfxVolume(float volume01);

        bool IsMusicPlaying() const;

    private:
        sf::Music backgroundMusic_;

        sf::SoundBuffer eatAppleBuffer_;
        sf::Sound eatAppleSound_;

        /// Normalized volume levels (0..1)
        float musicVolume01_ = 0.30F;
        float sfxVolume01_ = 0.60F;

        // Maximum physical volume levels
        static constexpr float k_MaxMusicVolume = 25.0F;
        static constexpr float k_MaxSfxVolume = 35.0F;
    };
}
