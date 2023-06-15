#include "spikes.h"

Spikes::Spikes()
{
    gonna_show = false;
    isHide = true;
}

Spikes::~Spikes()
{
}

void Spikes::Init(const sf::Texture& texture, float m_x, float m_y)
{
    setTexture(texture);
    setPosition(m_x, m_y);
    setVelocity(0,0);
}

void Spikes::setVelocity(float v_x, float v_y)
{
    this->vel_x = v_x;
    this->vel_y = v_y;
}

void Spikes::animation_left_show(const sf::Time elapsed)
{
    if(gonna_show)
    {
        if(getGlobalBounds().left < 50)
        {
            move(vel_x*elapsed.asSeconds(),0);
            isHide = false;
        }
    }
}

void Spikes::animation_right_show(const sf::Time elapsed)
{
    if(gonna_show)
    {
        if((getGlobalBounds().left + getGlobalBounds().width) > 600)
        {
            move(-vel_x*elapsed.asSeconds(),0);
            isHide = false;
        }
    }
}

void Spikes::animation_left_hide(const sf::Time elapsed)
{
    if(!isHide)
    {
        if(getGlobalBounds().left > 12)
        {
            move(-vel_x*elapsed.asSeconds(),0);
        }
        if(getGlobalBounds().left == 12)
        {
            isHide = true;
        }
    }
}

void Spikes::animation_right_hide(const sf::Time elapsed)
{
    if(!isHide)
    {
        if(getGlobalBounds().left < 593)
        {
            move(vel_x*elapsed.asSeconds(),0);
        }
        if(getGlobalBounds().left == 593)
        {
            isHide = true;
        }
    }
}
















