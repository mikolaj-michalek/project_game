#ifndef MAINMENU_H
#define MAINMENU_H

#include <memory>
#include <vector>
#include "bird.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "State.h"
#include "game.h"


class MainMenu : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameTitle;
    sf::Text m_gameInstruction_1;
    sf::Text m_gameInstruction_2;
    sf::Text m_gameInstruction_3;
    sf::Sprite m_menuBackground;
    bool isSpaceButtonPressed;
    bool isEscapeButtonPressed;

    Bird menu_bird;
    sf::Time m_elapsedTime;

public:
    MainMenu(std::shared_ptr<Context> &context);
    ~MainMenu();

    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time detlaTime) override;
    void Draw() override;
};

#endif // MAINMENU_H
