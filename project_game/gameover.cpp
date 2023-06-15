#include "gameover.h"
#include "gameplay.h"

GameOver::GameOver(std::shared_ptr<Context> &context)
    : m_context(context), isRetryButtonPressed(false), isCloseButtonPressed(false)
{

}

GameOver::~GameOver()
{

}

void GameOver::Init()
{
    m_context->m_assets->AddTexture(BACKGROUND_GAMEOVER, "assets/textures/background.png");
    m_gameOverBackground.setTexture(m_context->m_assets->GetTexture(BACKGROUND_GAMEOVER));

    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/pixel_font_7.ttf");
    m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameOverTitle.setString("GAME OVER");
    m_gameOverTitle.setStyle(sf::Text::Bold);
    m_gameOverTitle.setCharacterSize(72);
    m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2,
                          m_gameOverTitle.getLocalBounds().height / 2);
    m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2, 300);

    m_gameInstruction_1.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameInstruction_1.setString("TAP SPACE");
    m_gameInstruction_1.setStyle(sf::Text::Bold);
    m_gameInstruction_1.setCharacterSize(32);
    m_gameInstruction_1.setOrigin(m_gameInstruction_1.getLocalBounds().width / 2,
                                m_gameInstruction_1.getLocalBounds().height / 2);
    m_gameInstruction_1.setPosition(m_context->m_window->getSize().x / 2, 200);

    m_gameInstruction_2.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameInstruction_2.setString("TO RETRY");
    m_gameInstruction_2.setStyle(sf::Text::Bold);
    m_gameInstruction_2.setCharacterSize(32);
    m_gameInstruction_2.setOrigin(m_gameInstruction_2.getLocalBounds().width / 2,
                                  m_gameInstruction_2.getLocalBounds().height / 2);
    m_gameInstruction_2.setPosition(m_context->m_window->getSize().x / 2, 225);

    m_gameInstruction_3.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameInstruction_3.setString("TAP ESC TO EXIT");
    m_gameInstruction_3.setFillColor(sf::Color::White);
    m_gameInstruction_3.setStyle(sf::Text::Bold);
    m_gameInstruction_3.setCharacterSize(13);
    m_gameInstruction_3.setOrigin(m_gameInstruction_3.getLocalBounds().width / 2,
                                  m_gameInstruction_3.getLocalBounds().height / 2);
    m_gameInstruction_3.setPosition(m_context->m_window->getSize().x / 2, 255);
 }

void GameOver::ProcessInput()
{
    sf::Event ev;
    while (m_context->m_window->pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }

        isRetryButtonPressed = false;
        isCloseButtonPressed = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            isRetryButtonPressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            isCloseButtonPressed = true;
        }
    }
}

void GameOver::Update(sf::Time deltaTime)
{
    if(isRetryButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
    }
    if(isCloseButtonPressed)
    {
        m_context->m_window->close();
    }
}

void GameOver::Draw()
{
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_gameOverBackground);
    m_context->m_window->draw(m_gameOverTitle);
    m_context->m_window->draw(m_gameInstruction_1);
    m_context->m_window->draw(m_gameInstruction_2);
    m_context->m_window->draw(m_gameInstruction_3);
    m_context->m_window->display();
}
