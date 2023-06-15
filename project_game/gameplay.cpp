#include "gameplay.h"

GamePlay::GamePlay(std::shared_ptr<Context> &context)
    : m_context(context), isBackButtonPressed(false), m_elapsedTime(sf::Time::Zero)
{

}

GamePlay::~GamePlay()
{

}

void GamePlay::Init()
{
    m_context->m_assets->AddTexture(BACKGROUND, "assets/textures/background.png");
    m_context->m_assets->AddTexture(LEFT_WALL, "assets/textures/lewa_sciana.png");
    m_context->m_assets->AddTexture(RIGHT_WALL, "assets/textures/prawa_sciana.png");
    m_context->m_assets->AddTexture(BIRDGAME, "assets/textures/bird_gameplay.png");

    m_background.setTexture(m_context->m_assets->GetTexture(BACKGROUND));
    m_leftWall.setTexture(m_context->m_assets->GetTexture(LEFT_WALL));
    m_leftWall.setPosition(0,0);
    m_rightWall.setTexture(m_context->m_assets->GetTexture(RIGHT_WALL));
    m_rightWall.setPosition(592,0);

    m_bird.InitGamePlay(m_context->m_assets->GetTexture(BIRDGAME));
}
void GamePlay::ProcessInput()
{
    sf::Event ev;
    while (m_context->m_window->pollEvent(ev))
    {
        if (ev.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }

        isBackButtonPressed = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            isBackButtonPressed = true;
        }
    }
}
void GamePlay::Update(sf::Time deltaTime)
{
    m_elapsedTime += deltaTime;
    m_bird.animation(m_elapsedTime, timer);
    m_bird.collision(650, 800);
    m_bird.gravitation(m_elapsedTime);
    m_bird.rotation(m_elapsedTime);
    m_elapsedTime = sf::Time::Zero;
    if(m_bird.TimeToEnd)
    {
        //go to game over
        m_context->m_window->close();
    }

    if(isBackButtonPressed)
    {
        //back to menu(now closing window)
        m_context->m_window->close();
    }
}
void GamePlay::Draw()
{
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_background);
    m_context->m_window->draw(m_leftWall);
    m_context->m_window->draw(m_rightWall);
    m_context->m_window->draw(m_bird);
    m_context->m_window->display();
}
void GamePlay::Pause()
{
}
void GamePlay::Start()
{
}