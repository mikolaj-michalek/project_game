#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "State.h"
#include "game.h"
#include "bird.h"
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include "gameover.h"
#include "mainmenu.h"

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
