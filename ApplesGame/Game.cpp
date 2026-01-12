#include "Game.h"
#include "Constants.h"
#include "Math.h"
#include "RenderHelpers.h"
#include "UI.h"

namespace ApplesGame
{
    static void UpdatePlaying(Game& game, float deltaTimeSeconds)
    {
        HandleInput(game);
        UpdatePlayer(game.state.player, deltaTimeSeconds);

        if (HasPlayerCollisionWithScreenBorder(game.state.player))
        {
            game.state.mode = EGameMode::GameOver;
            game.ui.blinkTimerSeconds = 0.0F; // restart blinking
            return;
        }

        if (IsCirclesCollide(
            game.state.player.position, k_PlayerRadius,
            game.state.apple.position, k_AppleRadius))
        {
            game.state.score++;
            game.state.player.speed += k_Acceleration;

            game.audio.PlayEatApple();
            InitApple(game.state.apple, game.resources.appleTexture);

            UpdateUI(game.ui, game.state);
        }
    }

    bool InitGame(Game& game)
    {
        if (!LoadResources(game.resources))
        {
            return false;
        }

        if (!game.audio.Init(k_ResourcesPath))
        {
            return false;
        }
        game.audio.PlayMusic();

        game.backgroundSprite.setTexture(game.resources.backgroundTexture);
        FitSpriteToScreen(game.backgroundSprite, game.resources.backgroundTexture);

        game.menuBackgroundSprite.setTexture(game.resources.menuBackgroundTexture);
        FitSpriteToScreen(game.menuBackgroundSprite, game.resources.menuBackgroundTexture);

        InitUI(game.ui, game.resources);

        ResetGameplay(game);

        game.state.mode = EGameMode::MainMenu;
        game.ui.blinkTimerSeconds = 0.0F;

        return true;
    }

    void ResetGameplay(Game& game)
    {
        InitPlayer(game.state.player, game.resources.playerTexture);
        InitApple(game.state.apple, game.resources.appleTexture);

        game.state.score = 0;
        UpdateUI(game.ui, game.state);
    }

    void HandleInput(Game& game)
    {
        if (game.state.mode != EGameMode::Playing)
        {
            return;
        }

        Player& player = game.state.player;

        const bool rightPressed =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::D);

        const bool upPressed =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::W);

        const bool leftPressed =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::A);

        const bool downPressed =
            sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::S);

        if (rightPressed)
        {
            player.direction = EPlayerDirection::Right;
        }
        else if (upPressed)
        {
            player.direction = EPlayerDirection::Up;
        }
        else if (leftPressed)
        {
            player.direction = EPlayerDirection::Left;
        }
        else if (downPressed)
        {
            player.direction = EPlayerDirection::Down;
        }
    }

    void UpdateGame(Game& game, float deltaTimeSeconds)
    {
        switch (game.state.mode)
        {
        case EGameMode::MainMenu:
            UpdateMenuUI(game.ui, deltaTimeSeconds);
            break;

        case EGameMode::Playing:
            UpdatePlaying(game, deltaTimeSeconds);
            break;

        case EGameMode::GameOver:
            UpdateGameOverUI(game.ui, deltaTimeSeconds);
            break;
        }
    }

    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        if (game.state.mode == EGameMode::MainMenu)
        {
            DrawMenuUI(game.ui, window, game.menuBackgroundSprite);
            return;
        }

        window.draw(game.backgroundSprite);

        DrawUI(game.ui, window);

        game.state.player.sprite.setPosition(OurVectorToSf(game.state.player.position));
        ApplyPlayerSpriteTransform(game.state.player);
        window.draw(game.state.player.sprite);

        DrawApple(game.state.apple, window);

        if (game.state.mode == EGameMode::GameOver)
        {
            DrawGameOverOverlay(game.ui, window);
        }
    }
}
