#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include <vector>
#include "State.h"
#include "game.h"
#include "mainmenu.h"
#include "gameplay.h"
#include "coin.h"

class GameOver : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_gameOverBackground;
    sf::Text m_gameOverTitle;
    sf::Text m_gameInstruction_1;
    sf::Text m_gameInstruction_2;
    sf::Text m_gameInstruction_3;
    sf::Text finalScore;
    sf::Text finalCoins;
    sf::Time m_elapsedTime;

    Coin resultCoin;

    bool isRetryButtonPressed;
    bool isCloseButtonPressed;

    int m_score;
    int m_coins;

public:
    GameOver(std::shared_ptr<Context> &context, int birdScore, int coinsCollected);
    ~GameOver();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time detlaTime) override;
    void Draw() override;
};

#endif // GAMEOVER_H
