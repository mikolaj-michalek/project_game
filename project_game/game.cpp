#include "game.h"

Game::Game() : m_context(std::make_shared<Context>())
{
    m_context->m_window->create(sf::VideoMode(900, 600), "Spiky bird", sf::Style::Titlebar | sf::Style::Close);
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

//            m_context->m_states->ProcessStateChange();
//            m_context->m_states->GetCurrent()->ProcessInput();
//            m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
//            m_context->m_states->GetCurrent()->Draw();

            sf::Event ev;
            while (m_context->m_window->pollEvent(ev))
            {
                if (ev.type == sf::Event::Closed)
                {
                    m_context->m_window->close();
                }
            }

            m_context->m_window->clear(sf::Color::Black);

            m_context->m_window->display();
        }
    }
}
