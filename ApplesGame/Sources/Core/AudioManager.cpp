// @file AudioManager.cpp

#include "AudioManager.h"

#include "MathUtils.h"

namespace ApplesGame
{
    AudioManager::~AudioManager()
    {
        Shutdown();
    }

    bool AudioManager::Init(const std::string& resourcesPath)
    {
        const bool isMusicLoaded =
            m_BackgroundMusic.openFromFile(resourcesPath + "Audio/backgroundMusic.wav");

        const bool isEatAppleLoaded =
            m_EatAppleBuffer.loadFromFile(resourcesPath + "Audio/EatApple.wav");

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