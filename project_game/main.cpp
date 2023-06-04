#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

#include <iostream>

using namespace std;

int main()
{
    float window_x = 650.0;
    float window_y = 800.0;
    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "Spiky Birdy");
    window.setFramerateLimit(60);

    sf::Texture texture_background;
    if(!texture_background.loadFromFile("background.png")) { return 1; }

    sf::Texture texture_bird;
    if(!texture_bird.loadFromFile("bird_fly.png")) { return 1; }

    sf::Sprite background;
    background.setTexture(texture_background);

    sf::Sprite bird;
    bird.setTexture(texture_bird);
    bird.setPosition(310, 380);

    float birdSpeed = 3.0f;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2f movement(0.0f, 0.0f);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            movement.y -= birdSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            movement.y += birdSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            movement.x -= birdSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            movement.x += birdSpeed;

        // Aktualizacja pozycji ptaka
        sf::Vector2f newPosition = bird.getPosition() + movement;

        bird.setPosition(newPosition);

        window.draw(background);

        window.draw(bird);

        window.display();
    }
}
