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
    float vel_r = 0.0;
    float g_force = 0;
    int lives = 1;
    int score = 0;

public:
    Bird();
    ~Bird();

    void add_animation_frame(const sf::IntRect &frame);
    void step(const sf::Time elapsed);
    void InitGamePlay(const sf::Texture& texture);
    void InitMainMenu(const sf::Texture& texture);
    void setVelocity(float v_x, float v_y);
    void setRotation(float v_r);
    void animation(const sf::Time elapsed, sf::Clock &realtimer);
    void gravitation(const sf::Time elapsed);
    void rotation(const sf::Time elapsed);
    void collision(float win_x, float win_y);
    void toLeft();
    void toRight();
    void change_look_normal();
    void change_look_space();
    void change_look_die();
    void setStartPosition();
    void setLives(int i);
    void setScore(int i);
    int getLives();
    int getScore();
    bool isDead;
    bool TimeToEnd;
    bool isTextureChanged;
};

#endif // BIRD_H
