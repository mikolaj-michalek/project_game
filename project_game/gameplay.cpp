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
    m_context->m_assets->AddTexture(BIRDGAME, "assets/textures/bird_gameplay_2.png");
    m_context->m_assets->AddTexture(LEFT_SPIKE, "assets/textures/kolec_lewy.png");
    m_context->m_assets->AddTexture(RIGHT_SPIKE, "assets/textures/kolec_prawy.png");
//    m_context->m_assets->AddTexture(BACKGROUND2, "assets/textures/background_2.png");
//    m_context->m_assets->AddTexture(BACKGROUND3, "assets/textures/background_3.png");
//    m_context->m_assets->AddTexture(BACKGROUND4, "assets/textures/background_4.png");
//    m_context->m_assets->AddTexture(BACKGROUND5, "assets/textures/background_5.png");
//    m_context->m_assets->AddTexture(BACKGROUND6, "assets/textures/background_6.png");

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
    for(size_t i=0; i<13; i++)
    {
        left_spikes[i].Init(m_context->m_assets->GetTexture(LEFT_SPIKE), 12, (i*49+82));
        right_spikes[i].Init(m_context->m_assets->GetTexture(RIGHT_SPIKE), 593, (i*49+82));
        left_spikes[i].setVelocity(100,0);
        right_spikes[i].setVelocity(100,0);
    }
    for (int i = 1; i <= 13; ++i)
    {
        numbers.push_back(i);
    }

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
    sf::FloatRect bird_bounds = m_bird.getGlobalBounds();
    sf::FloatRect bird_hitbox = bird_bounds;
    bird_hitbox.width *= 1;
    bird_hitbox.height *= 0.1;
    m_score = m_bird.getScore();
    numbers = m_bird.chosennumbers;
    for(size_t i=0; i<13; i++)
    {
        sf::FloatRect spikeL_bounds = left_spikes[i].getGlobalBounds();
        sf::FloatRect spikeR_bounds = right_spikes[i].getGlobalBounds();

        if (bird_hitbox.intersects(spikeL_bounds))
        {
            m_bird.isDead = true;
            m_bird.change_look_die();
        }
        if (bird_hitbox.intersects(spikeR_bounds))
        {
            m_bird.isDead = true;
            m_bird.change_look_die();
        }

        if(m_bird.isDead)
        {
            left_spikes[i].animation_left_hide(m_elapsedTime);
            right_spikes[i].animation_right_hide(m_elapsedTime);
        }
        else
        {
            if(m_bird.hitLeft)
            {
                left_spikes[i].animation_left_hide(m_elapsedTime);
                for (int number : numbers)
                {
                    right_spikes[number].gonna_show = true;
                }
                right_spikes[i].animation_right_show(m_elapsedTime);
                left_spikes[i].gonna_show = false;
            }
            if(m_bird.hitRight)
            {
                right_spikes[i].animation_right_hide(m_elapsedTime);
                for (int number : numbers)
                {
                    left_spikes[number].gonna_show = true;
                }
                left_spikes[i].animation_left_show(m_elapsedTime);
                right_spikes[i].gonna_show = false;
            }
        }
    }
    numbers.clear();
    m_bird.chosennumbers.clear();
    m_elapsedTime = sf::Time::Zero;
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
    for(size_t i=0; i<13; i++)
    {
        m_context->m_window->draw(left_spikes[i]);
        m_context->m_window->draw(right_spikes[i]);
    }
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
