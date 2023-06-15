#include "bird.h"
#include <iostream>

Bird::Bird()
{
    isDead = false;
    TimeToEnd = false;
    isTextureChanged = false;
}

Bird::~Bird()
{
}

void Bird::add_animation_frame(const sf::IntRect &frame)
{
    frames.emplace_back(frame);
    current_frame = frames.begin();
}

void Bird::step(const sf::Time elapsed)
{
    elapsed_accumulator += elapsed.asSeconds();
    while (elapsed_accumulator >= 1.0/fps)
    {
        elapsed_accumulator -= 1.0/fps;
        if (!frames.empty())
        {
            setTextureRect(*current_frame);
            current_frame++;
            if(current_frame == frames.end())
            {
                current_frame = frames.begin();
            }
        }
    }
}

void Bird::InitGamePlay(const sf::Texture& texture)
{
    setTexture(texture);                                                                   //inicjalizacja tekstury
    setTextureRect(sf::IntRect(0, 15, 121, 75));                                           //wyciecie poczatkowej tekstury
    setPosition(325, 400);                                                                 //ustalenie pozycji
    setVelocity(220,0);
    setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
    g_force = 750;
}

void Bird::InitMainMenu(const sf::Texture& texture)
{
    setTexture(texture);                                                                    //inicjalizacja tekstury
    setTextureRect(sf::IntRect(0, 0, 80, 75));                                             //wyciêcie poczatkowej tekstury
    setPosition(325, 400);
    setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
}

void Bird::setVelocity(float v_x, float v_y)
{
    vel_x = v_x;
    vel_y = v_y;
}

void Bird::setRotation(float v_r)
{
    vel_r = v_r;
}
void Bird::animation(const sf::Time elapsed, sf::Clock& realtimer)
{
    if(!isDead)
    {
        static bool isSpacePressed = false;
        static bool isTextureChanged = false;
        static sf::Time textureChangeDuration = sf::seconds(0.2f); // Czas trwania zmiany tekstury (0.1 sekundy w przykładzie)

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isSpacePressed)
        {
            isSpacePressed = true;
            vel_y = -290;
            if (!isTextureChanged)
            {
                change_look_space();
                isTextureChanged = true;
                realtimer.restart();
            }
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            isSpacePressed = false;
        }

        // Sprawdzenie czasu trwania zmiany tekstury
        if (isTextureChanged && realtimer.getElapsedTime() >= textureChangeDuration)
        {
            change_look_normal();
            isTextureChanged = false;
        }
    }
    move(vel_x * elapsed.asSeconds(), vel_y * elapsed.asSeconds());
}

void Bird::gravitation(const sf::Time elapsed)
{
    vel_y += g_force*elapsed.asSeconds();
    move(vel_x*elapsed.asSeconds(), vel_y*elapsed.asSeconds());
}

void Bird::rotation(const sf::Time elapsed)
{
    rotate(vel_r*elapsed.asSeconds());
}

void Bird::collision(float win_x, float win_y)
{
    sf::FloatRect bird_bounds = getGlobalBounds();

    if((bird_bounds.left+bird_bounds.width) >= (win_x-58))
    {
        toLeft();
    }
    if(bird_bounds.left <= 58)
    {
        toRight();
    }
    if(bird_bounds.top <= 61)
    {
        isDead = true;
        change_look_die();
        setRotation(1000);
        if(g_force < 10000)
        {
            g_force *= 1.08;
            setVelocity(vel_x,vel_y);
        }
        else
        {
            setVelocity(0,0);
            setStartPosition();
            g_force = 0;
            setTextureRect(sf::IntRect(0, 0, 1, 1));
            TimeToEnd = true;
        }
        vel_y = -(vel_y);
    }
    if((bird_bounds.top+bird_bounds.height) >= (win_y-59))
    {
        isDead = true;
        change_look_die();
        setRotation(1000);
        if(g_force < 6000)
        {
           g_force *= 1.09;
           setVelocity(vel_x,150);
        }
        else
        {

            setVelocity(0,0);
            setStartPosition();
            g_force = 0;
            setTextureRect(sf::IntRect(0, 0, 1, 1));
            TimeToEnd = true;
        }
        vel_y = -(vel_y);

    }
}

void Bird::toLeft()
{
    vel_x = -(vel_x);
    setScale(-1,1);
    if(!isDead)
    {
        score++;
        std::cout << "Score: " << score << std::endl;
    }
}

void Bird::toRight()
{
    vel_x = -(vel_x);
    setScale(1,1);
    if(!isDead)
    {
        score++;
        std::cout << "Score: " << score << std::endl;
    }
}

void Bird::change_look_normal()
{
    setTextureRect(sf::IntRect(0, 15, 121, 75));
    setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
}

void Bird::change_look_space()
{
    setTextureRect(sf::IntRect(130, 0, 121, 75));
    setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
}

void Bird::change_look_die()
{
    setTextureRect(sf::IntRect(260, 0, 97, 75));
    setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
}

void Bird::setStartPosition()
{
    setPosition(265, 363);
    toRight();
}

void Bird::setLives(int i)
{
    lives = i;
}

void Bird::setScore(int i)
{
    score = i;
}

int Bird::getLives()
{
    return lives;
}

int Bird::getScore()
{
    return score;
}









































































