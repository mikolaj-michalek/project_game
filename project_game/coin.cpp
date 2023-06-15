#include "coin.h"
#include <iostream>

Coin::Coin()
{
    is_collect = false;
    is_show = false;
}

Coin::~Coin()
{
}

void Coin::add_animation_frame(const sf::IntRect &frame)
{
    frames.emplace_back(frame);
    current_frame = frames.begin();
}

void Coin::step(const sf::Time elapsed)
{
    elapsed_accumulator += elapsed.asSeconds();
    while (elapsed_accumulator >= 0.4/fps)
    {
        elapsed_accumulator -= 0.4/fps;
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

void Coin::Init(const sf::Texture& texture, float m_x, float m_y)
{
    this->setTexture(texture);
    this->setTextureRect(sf::IntRect(0, 0, 25, 25));
    this->setPosition(m_x, m_y);
    this->setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
}

void Coin::show_coin()
{

}

void Coin::hide_coin()
{

}

