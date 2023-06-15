#include "game.h"
#include "mainmenu.h"

Game::Game() : m_context(std::make_shared<Context>())
{
    m_context->m_window->create(sf::VideoMode(650, 800), "Spiky bird", sf::Style::Titlebar | sf::Style::Close);
    m_context->m_states->Add(std::make_unique<MainMenu>(m_context));
}

Game::~Game()
{
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeElapsed = sf::Time::Zero;

    //Game loop
    while (m_context->m_window->isOpen())
    {
        timeElapsed += clock.restart();

        while(timeElapsed > TIME_PER_FRAME)
        {
            timeElapsed -= TIME_PER_FRAME;

            m_context->m_states->ProcessStateChange();
            m_context->m_states->GetCurrent()->ProcessInput();
            m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
            m_context->m_states->GetCurrent()->Draw();
        }
    }
}
