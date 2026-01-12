#include "AudioManager.h"
#include <algorithm>

namespace ApplesGame
{
    static float Clamp01(float v)
    {
        return std::max(0.0F, std::min(1.0F, v));
    }

    bool AudioManager::Init(const std::string& resourcesPath)
    {
        const bool isMusicLoaded =
            backgroundMusic_.openFromFile(resourcesPath + "Audio/backgroundMusic.wav");

        const bool isEatAppleLoaded =
            eatAppleBuffer_.loadFromFile(resourcesPath + "Audio/EatApple.wav");

        if (!isMusicLoaded || !isEatAppleLoaded)
        {
            return false;
        }

        eatAppleSound_.setBuffer(eatAppleBuffer_);
        backgroundMusic_.setLoop(true);

        SetMusicVolume(musicVolume01_);
        SetSfxVolume(sfxVolume01_);

        return true;
    }

    void AudioManager::SetMusicVolume(float volume01)
    {
        musicVolume01_ = Clamp01(volume01);
        backgroundMusic_.setVolume(musicVolume01_ * k_MaxMusicVolume);
    }

    void AudioManager::SetSfxVolume(float volume01)
    {
        sfxVolume01_ = Clamp01(volume01);
        eatAppleSound_.setVolume(sfxVolume01_ * k_MaxSfxVolume);
    }

    void AudioManager::PlayMusic()
    {
        if (backgroundMusic_.getStatus() != sf::Music::Playing)
        {
            backgroundMusic_.play();
        }
    }

    void AudioManager::PauseMusic()
    {
        if (backgroundMusic_.getStatus() == sf::Music::Playing)
        {
            backgroundMusic_.pause();
        }
    }

    void AudioManager::StopMusic()
    {
        backgroundMusic_.stop();
    }

    void AudioManager::PlayEatApple()
    {
        eatAppleSound_.play();
    }

    bool AudioManager::IsMusicPlaying() const
    {
        return backgroundMusic_.getStatus() == sf::Music::Playing;
    }
}
