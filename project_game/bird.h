#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
#include "game.h"

class Bird : public sf::Sprite
{
private:
    sf::Texture texture;
    std::vector<sf::IntRect> frames;
    std::vector<sf::IntRect>::iterator current_frame = frames.begin();
    float elapsed_accumulator = 0;
    float fps = 10.0;
    float vel_x = 0.0;
    float vel_y = 0.0;
    int lives = 1;
    int score = 0;

public:
    Bird();
    ~Bird();

    void add_animation_frame(const sf::IntRect &frame);
    void step(const sf::Time &elapsed);
    void setVelocity(float v_x, float v_y);
    void animation(const sf::Time &elapsed);
    void gravitation(const sf::Time &elapsed);
    void collision(float win_x, float win_y);
    void toLeft();
    void toRight();
    void setStartPosition();
    void Init(const sf::Texture& texture);
    void setLives(int i);
    void setScore(int i);
    int getLives();
    int getScore();
};

#endif // BIRD_H
