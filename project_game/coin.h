#ifndef COIN_H
#define COIN_H

#include <SFML/Graphics.hpp>
#include "game.h"
#include <vector>

class Coin : public sf::Sprite
{
private:
    sf::Texture coin_texture;
    std::vector<sf::IntRect> frames;
    std::vector<sf::IntRect>::iterator current_frame = frames.begin();
    float elapsed_accumulator = 0;
    float fps = 10.0;


public:
    Coin();
    ~Coin();

    void add_animation_frame(const sf::IntRect &frame);
    void step(const sf::Time elapsed);
    void Init(const sf::Texture& texture, float m_x, float m_y);
    void show_coin();
    void hide_coin();
    bool is_collect;
    bool is_show;
};

#endif // COIN_H
