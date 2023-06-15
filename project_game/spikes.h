#ifndef SPIKES_H
#define SPIKES_H

#include <SFML/Graphics.hpp>
#include "game.h"

class Spikes : public sf::Sprite
{
private:
    sf::Texture texture;
    float vel_x = 0.0;
    float vel_y = 0.0;

public:
    Spikes();
    ~Spikes();

    void Init(const sf::Texture& texture, float m_x, float m_y);
    void setVelocity(float v_x, float v_y);
    void animation_left_show(const sf::Time elapsed);
    void animation_right_show(const sf::Time elapsed);
    void animation_left_hide(const sf::Time elapsed);
    void animation_right_hide(const sf::Time elapsed);
    bool gonna_show;
    bool isHide;
};

#endif // SPIKES_H
