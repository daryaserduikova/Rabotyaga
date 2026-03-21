#include "AudioManager.h"
#include "MathUtils.h"
#include <iostream>

namespace ApplesGame
{
    AudioManager::~AudioManager()
    {
        Shutdown();
    }

    bool AudioManager::Init(const std::string& resourcesPath)
    {
        const std::string musicPath = resourcesPath + "Audio/backgroundMusic.wav";
        const std::string sfxPath = resourcesPath + "Audio/EatApple.wav";

        const bool isMusicLoaded = m_BackgroundMusic.openFromFile(musicPath);
        const bool isEatAppleLoaded = m_EatAppleBuffer.loadFromFile(sfxPath);

        if (!isMusicLoaded)
        {
            std::cout << "Music NOT loaded: " << musicPath << "\n";
        }

        if (!isEatAppleLoaded)
        {
            std::cout << "SFX NOT loaded: " << sfxPath << "\n";
        }

        if (!isMusicLoaded || !isEatAppleLoaded)
        {
            return false;
        }

        m_EatAppleSound.setBuffer(m_EatAppleBuffer);
        m_BackgroundMusic.setLoop(true);

        SetMusicVolume(m_MusicVolume01);
        SetSfxVolume(m_SfxVolume01);

        return true;
    }

    void AudioManager::Shutdown()
    {
        m_EatAppleSound.stop();
        m_BackgroundMusic.stop();
    }

    void AudioManager::SetMusicVolume(float volume01)
    {
        m_MusicVolume01 = Clamp(volume01, 0.0F, 1.0F);
        m_BackgroundMusic.setVolume(m_MusicVolume01 * k_MaxMusicVolume);
    }

    void AudioManager::SetSfxVolume(float volume01)
    {
        m_SfxVolume01 = Clamp(volume01, 0.0F, 1.0F);
        m_EatAppleSound.setVolume(m_SfxVolume01 * k_MaxSfxVolume);
    }

    void AudioManager::PlayMusic()
    {
        if (m_BackgroundMusic.getStatus() != sf::Music::Playing)
        {
            m_BackgroundMusic.play();
        }
    }

    void AudioManager::PauseMusic()
    {
        if (m_BackgroundMusic.getStatus() == sf::Music::Playing)
        {
            m_BackgroundMusic.pause();
        }
    }

    void AudioManager::StopMusic()
    {
        m_BackgroundMusic.stop();
    }

    void AudioManager::PlayEatApple()
    {
        m_EatAppleSound.play();
    }

    bool AudioManager::IsMusicPlaying() const
    {
        return m_BackgroundMusic.getStatus() == sf::Music::Playing;
    }
}