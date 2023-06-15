#ifndef PAUSEGAME_H
#define PAUSEGAME_H

#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.h"
#include "game.h"

class PauseGame : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_pauseTitle;
    sf::Sprite m_pauseBackground;

public:
    PauseGame(std::shared_ptr<Context> &context);
    ~PauseGame();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time detlaTime) override;
    void Draw() override;
};

#endif // PAUSEGAME_H
