#include "mainmenu.h"

MainMenu::MainMenu(std::shared_ptr<Context> &context)
    : m_context(context), isSpaceButtonPressed(false), isEscapeButtonPressed(false)
{

}

MainMenu::~MainMenu()
{

}

void MainMenu::Init()
{
    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/pixel_font_7.ttf");
    m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameTitle.setString("SPIKY BIRD");
    m_gameTitle.setStyle(sf::Text::Bold);
    m_gameTitle.setCharacterSize(72);
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2,
                          m_gameTitle.getLocalBounds().height / 2);
    m_gameTitle.setPosition(m_context->m_window->getSize().x / 2, 100);

    m_gameInstruction_1.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameInstruction_1.setString("TAP SPACE");
    m_gameInstruction_1.setStyle(sf::Text::Bold);
    m_gameInstruction_1.setCharacterSize(32);
    m_gameInstruction_1.setOrigin(m_gameInstruction_1.getLocalBounds().width / 2,
                                m_gameInstruction_1.getLocalBounds().height / 2);
    m_gameInstruction_1.setPosition(m_context->m_window->getSize().x / 2, 200);

    m_gameInstruction_2.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameInstruction_2.setString("TO JUMP");
    m_gameInstruction_2.setStyle(sf::Text::Bold);
    m_gameInstruction_2.setCharacterSize(32);
    m_gameInstruction_2.setOrigin(m_gameInstruction_2.getLocalBounds().width / 2,
                                  m_gameInstruction_2.getLocalBounds().height / 2);
    m_gameInstruction_2.setPosition(m_context->m_window->getSize().x / 2, 225);

    m_gameInstruction_3.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameInstruction_3.setString("TAP ESC TO EXIT");
    m_gameInstruction_3.setFillColor(sf::Color::Blue);
    m_gameInstruction_3.setStyle(sf::Text::Bold);
    m_gameInstruction_3.setCharacterSize(22);
    m_gameInstruction_3.setOrigin(m_gameInstruction_3.getLocalBounds().width / 2,
                                  m_gameInstruction_3.getLocalBounds().height / 2);
    m_gameInstruction_3.setPosition(m_context->m_window->getSize().x / 2, 700);
 }

void MainMenu::ProcessInput()
{
    sf::Event ev;
    while (m_context->m_window->pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }

        isSpaceButtonPressed = false;
        isEscapeButtonPressed = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            isSpaceButtonPressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            isEscapeButtonPressed = true;
        }
    }
}

void MainMenu::Update(sf::Time deltaTime)
{
    if(isSpaceButtonPressed)
    {
        //go to play state
    }
    if(isEscapeButtonPressed)
    {
        m_context->m_window->close();
    }
}

void MainMenu::Draw()
{

    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_gameInstruction_1);
    m_context->m_window->draw(m_gameInstruction_2);
    m_context->m_window->draw(m_gameInstruction_3);
    m_context->m_window->display();
}
