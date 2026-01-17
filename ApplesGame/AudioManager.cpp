#include "AudioManager.h"
#include <algorithm>

namespace ApplesGame
{
    static float Clamp01(float v)
    {
        return std::max(0.0F, std::min(1.0F, v));
    }

    AudioManager::~AudioManager()
    {
        Shutdown();
    }

    bool AudioManager::Init(const std::string& resourcesPath)
    {
        const bool isMusicLoaded =
            m_backgroundMusic.openFromFile(resourcesPath + "Audio/backgroundMusic.wav");

        const bool isEatAppleLoaded =
            m_eatAppleBuffer.loadFromFile(resourcesPath + "Audio/EatApple.wav");

        if (!isMusicLoaded || !isEatAppleLoaded)
        {
            return false;
        }

        m_eatAppleSound.setBuffer(m_eatAppleBuffer);
        m_backgroundMusic.setLoop(true);

        SetMusicVolume(m_musicVolume01);
        SetSfxVolume(m_sfxVolume01);

        return true;
    }

    void AudioManager::Shutdown()
    {
        m_eatAppleSound.stop();
        m_backgroundMusic.stop();
    }

    void AudioManager::SetMusicVolume(float volume01)
    {
        m_musicVolume01 = Clamp01(volume01);
        m_backgroundMusic.setVolume(m_musicVolume01 * k_MaxMusicVolume);
    }

    void AudioManager::SetSfxVolume(float volume01)
    {
        m_sfxVolume01 = Clamp01(volume01);
        m_eatAppleSound.setVolume(m_sfxVolume01 * k_MaxSfxVolume);
    }

    void AudioManager::PlayMusic()
    {
        if (m_backgroundMusic.getStatus() != sf::Music::Playing)
        {
            m_backgroundMusic.play();
        }
    }

    void AudioManager::PauseMusic()
    {
        if (m_backgroundMusic.getStatus() == sf::Music::Playing)
        {
            m_backgroundMusic.pause();
        }
    }

    void AudioManager::StopMusic()
    {
        m_backgroundMusic.stop();
    }

    void AudioManager::PlayEatApple()
    {
        m_eatAppleSound.play();
    }

    bool AudioManager::IsMusicPlaying() const
    {
        return m_backgroundMusic.getStatus() == sf::Music::Playing;
    }
}
