#include "pausegame.h"

PauseGame::PauseGame(std::shared_ptr<Context> &context)
    : m_context(context)
{
}

PauseGame::~PauseGame()
{
}

void PauseGame::Init()
{
    m_pauseBackground.setTexture(m_context->m_assets->GetTexture(BACKGROUND));

    m_pauseTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_pauseTitle.setString("PAUSED");
    m_pauseTitle.setStyle(sf::Text::Bold);
    m_pauseTitle.setCharacterSize(72);
    m_pauseTitle.setOrigin(m_pauseTitle.getLocalBounds().width / 2, m_pauseTitle.getLocalBounds().height / 2);
    m_pauseTitle.setPosition(m_context->m_window->getSize().x / 2, 300);
}

void PauseGame::ProcessInput()
{
    sf::Event ev;
    while (m_context->m_window->pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            m_context->m_states->PopCurrent();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            m_context->m_window->close();
        }
    }
}

void PauseGame::Update(sf::Time deltaTime)
{
}

void PauseGame::Draw()
{
    m_context->m_window->draw(m_pauseBackground);
    m_context->m_window->draw(m_pauseTitle);
    m_context->m_window->display();
}
