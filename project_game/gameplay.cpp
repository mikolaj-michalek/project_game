#include "gameplay.h"

GamePlay::GamePlay(std::shared_ptr<Context> &context)
    : m_context(context), isBackButtonPressed(false), m_elapsedTime(sf::Time::Zero), m_score(0)
{

}

GamePlay::~GamePlay()
{

}

void GamePlay::Init()
{
    m_context->m_assets->AddTexture(LEFT_WALL, "assets/textures/lewa_sciana.png");
    m_context->m_assets->AddTexture(RIGHT_WALL, "assets/textures/prawa_sciana.png");
    m_context->m_assets->AddTexture(BIRDGAME, "assets/textures/bird_gameplay.png");

    m_background.setTexture(m_context->m_assets->GetTexture(BACKGROUND));
    m_leftWall.setTexture(m_context->m_assets->GetTexture(LEFT_WALL));
    m_leftWall.setPosition(1,0);
    m_rightWall.setTexture(m_context->m_assets->GetTexture(RIGHT_WALL));
    m_rightWall.setPosition(593,0);

    m_bird.InitGamePlay(m_context->m_assets->GetTexture(BIRDGAME));

    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreText.setString("0");
    m_scoreText.setStyle(sf::Text::Bold);
    m_scoreText.setCharacterSize(108);
    m_scoreText.setOrigin(m_scoreText.getLocalBounds().width / 2,
                          m_scoreText.getLocalBounds().height / 2);
    m_scoreText.setPosition(m_context->m_window->getSize().x / 2, 100);

    m_pauseInfo.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_pauseInfo.setString("TAP P TO PAUSE       TAP ESC TO MENU");
    m_pauseInfo.setStyle(sf::Text::Bold);
    m_pauseInfo.setCharacterSize(16);
    m_pauseInfo.setOrigin(m_pauseInfo.getLocalBounds().width / 2,
                          m_pauseInfo.getLocalBounds().height / 2);
    m_pauseInfo.setPosition(m_context->m_window->getSize().x / 2, 785);
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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            m_context->m_states->Add(std::make_unique<PauseGame>(m_context));
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
    m_score = m_bird.getScore();
    m_scoreText.setString(std::to_string(m_score));
    m_scoreText.setOrigin(m_scoreText.getLocalBounds().width / 2,
                          m_scoreText.getLocalBounds().height / 2);
    m_scoreText.setPosition(m_context->m_window->getSize().x / 2, 100);
    if(m_bird.TimeToEnd)
    {
        m_context->m_states->Add(std::make_unique<GameOver>(m_context, m_score), true);
    }

    if(isBackButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
    }
}
void GamePlay::Draw()
{
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(m_background);
    m_context->m_window->draw(m_leftWall);
    m_context->m_window->draw(m_rightWall);
    m_context->m_window->draw(m_scoreText);
    m_context->m_window->draw(m_pauseInfo);
    m_context->m_window->draw(m_bird);
    m_context->m_window->display();
}
void GamePlay::Pause()
{
}
void GamePlay::Start()
{
}
