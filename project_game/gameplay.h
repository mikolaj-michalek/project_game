#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <memory>
#include "State.h"
#include "game.h"
#include "bird.h"
#include "spikes.h"
#include "coin.h"
#include "gameover.h"
#include "mainmenu.h"
#include "pausegame.h"


class GamePlay : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    bool isBackButtonPressed;

    sf::Sprite m_background;
    sf::Sprite m_leftWall;
    sf::Sprite m_rightWall;

    Bird m_bird;
    sf::Time m_elapsedTime;
    sf::Clock timer;
    Spikes left_spikes[13];
    Spikes right_spikes[13];

    Coin left_coin;
    Coin right_coin;

    sf::Text m_scoreText;
    sf::Text m_pauseInfo;
    int m_score;

    std::vector<int> numbers;


public:
    GamePlay(std::shared_ptr<Context> &context);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw() override;

    void Pause() override;
    void Start() override;
};

#endif // GAMEPLAY_H
