#include "bird.h"
#include <iostream>

Bird::Bird()
{
    isDead = false;
    TimeToEnd = false;
    hitLeft = false;
    hitRight = false;
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
    while (elapsed_accumulator >= 1.75/fps)
    {
        elapsed_accumulator -= 1.75/fps;
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
    this->setTexture(texture);
    this->setTextureRect(sf::IntRect(0, 14, 107, 40));
    this->setPosition(325, 400);
    this->setVelocity(220, -290);
    this->setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
    this->g_force = 750;
    this->currentLevel = 1;
    this->howManySpikes = 2;

    this->numbers.clear();
    for (int i = 0; i < 13; ++i)
    {
        this->numbers.push_back(i);
    }
}

void Bird::InitMainMenu(const sf::Texture& texture)
{
    this->setTexture(texture);
    this->setTextureRect(sf::IntRect(0, 0, 84, 75));
    this->setPosition(325, 400);
    this->setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
}

void Bird::setVelocity(float v_x, float v_y)
{
    this->vel_x = v_x;
    this->vel_y = v_y;
}

void Bird::setRotation(float v_r)
{
    this->vel_r = v_r;
}
void Bird::animation(const sf::Time elapsed, sf::Clock& realtimer)
{
    switch(this->currentLevel)
    {
    case 1:
        this->howManySpikes = 2;
        this->g_force *= 1;
        this->setScale(getScale().x, 1);
        break;
    case 2:
        this->howManySpikes = 1;
        if(this->g_force>0)
        {
           this->g_force *= -1;
        }
        this->setScale(getScale().x, -1);
        break;
    case 3:
        this->howManySpikes = 3;
        if(this->g_force<0)
        {
           this->g_force *= -1;
        }
        this->setScale(getScale().x, 1);
        break;
    case 4:
        this->howManySpikes = 2;
        if(this->g_force>0)
        {
           this->g_force *= -1;
        }
        this->setScale(getScale().x, -1);
        break;
    case 5:
        this->howManySpikes = 4;
        if(this->g_force<0)
        {
           this->g_force *= -1;
        }
        this->setScale(getScale().x, 1);
        break;
    case 6:
        this->howManySpikes = 3;
        if(this->g_force>0)
        {
           this->g_force *= -1;
        }
        this->setScale(getScale().x, -1);
        break;
    case 7:
        this->howManySpikes = 5;
        if(this->g_force<0)
        {
           this->g_force *= -1;
        }
        this->setScale(getScale().x, 1);
        break;
    default:
        this->howManySpikes = 2;
        this->g_force *= 1;
        this->setScale(getScale().x, 1);
        break;
    }
    if(!isDead)
    {
        static bool isSpacePressed = false;
        static bool isTextureChanged = false;
        static sf::Time textureChangeDuration = sf::seconds(0.2f); // Czas trwania zmiany tekstury (0.1 sekundy w przykładzie)

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isSpacePressed)
        {
            isSpacePressed = true;
            if((currentLevel%2) == 1)
            {
                vel_y = -290;
            }
            if((currentLevel%2) == 0)
            {
                vel_y = 290;
            }
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
    this->vel_y += g_force*elapsed.asSeconds();
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
    if((currentLevel%2) == 1)
    {
        if(bird_bounds.top <= 61)
        {
            change_look_die();
            if(g_force < 5000)
            {
                g_force *= 1.09;
                setVelocity(vel_x,-150);
            }
            else
            {
                setStartPosition();
                setTextureRect(sf::IntRect(0, 0, 1, 1));
                TimeToEnd = true;
            }
            this->vel_y = -(vel_y);
        }
        if((bird_bounds.top+bird_bounds.height) >= (win_y-59))
        {
            change_look_die();
            if(g_force < 5000)
            {
                g_force *= 1.09;
                setVelocity(vel_x,150);
            }
            else
            {
                setStartPosition();
                setTextureRect(sf::IntRect(0, 0, 1, 1));
                TimeToEnd = true;
            }
            this->vel_y = -(vel_y);
        }
    }
    if((currentLevel%2) == 0)
    {
        bird_bounds = getGlobalBounds();

        if(bird_bounds.top <= 61)
        {
            change_look_die();
            this->g_force *= -1;
            if(g_force < 2000)
            {
                g_force *= 1.09;
                setVelocity(vel_x, -150);
            }
            else
            {
                setStartPosition();
                setTextureRect(sf::IntRect(0, 0, 1, 1));
                TimeToEnd = true;
            }
            this->vel_y = -(vel_y);
        }
        if((bird_bounds.top+bird_bounds.height) >= (win_y-59))
        {
            change_look_die();
            this->g_force *= -1;
            if(g_force < 2000)
            {
                g_force *= 1.09;
                setVelocity(vel_x, 150);
            }
            else
            {
                setStartPosition();
                setTextureRect(sf::IntRect(0, 0, 1, 1));
                TimeToEnd = true;
            }
            this->vel_y = -(vel_y);
        }
    }
}

std::vector<int> Bird::losowanie(std::vector<int> numb, int m_amount)
{
    this->chosennumbers.clear();
    numb = this->numbers;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(numb.begin(), numb.end(), generator);
    chosennumbers.insert(chosennumbers.end(), numb.begin(), numb.begin() + m_amount);
    numb.clear();
    return chosennumbers;
}

void Bird::toLeft()
{
    vel_x = -(vel_x);
    setScale(-1,getScale().y);
    hitRight = true;
    hitLeft = false;
    losowanie(numbers, howManySpikes);
    if(!isDead)
    {
        score++;
    }
}

void Bird::toRight()
{
    vel_x = -(vel_x);
    setScale(1,getScale().y);
    hitRight = false;
    hitLeft = true;
    losowanie(numbers, howManySpikes);
    if(!isDead)
    {
        score++;
    }
}

void Bird::change_look_normal()
{
    setTextureRect(sf::IntRect(0, 14, 107, 40));
    setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
    isDead = false;
}

void Bird::change_look_space()
{
    setTextureRect(sf::IntRect(115, 0, 107, 67));
    setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
    isDead = false;
}

void Bird::change_look_die()
{
    setTextureRect(sf::IntRect(231, 0, 86, 67));
    setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
    isDead = true;
    setRotation(1000);
}

void Bird::setStartPosition()
{
    setPosition(325, 400);
    toRight();
    setVelocity(0,0);
    this->g_force = 0;
}

int Bird::getScore()
{
    return score;
}
