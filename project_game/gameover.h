#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <memory>
#include <vector>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.h"
#include "game.h"
#include "mainmenu.h"
#include "gameplay.h"

class GameOver : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameOverTitle;
    sf::Text m_gameInstruction_1;
    sf::Text m_gameInstruction_2;
    sf::Text m_gameInstruction_3;
    sf::Text finalScore;
    sf::Sprite m_gameOverBackground;
    bool isRetryButtonPressed;
    bool isCloseButtonPressed;

    int m_score;

public:
    GameOver(std::shared_ptr<Context> &context, int birdScore);
    ~GameOver();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time detlaTime) override;
    void Draw() override;
};


#endif // GAMEOVER_H
