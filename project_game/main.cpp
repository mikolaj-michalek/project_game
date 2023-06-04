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
    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "SPIKY BIRD");
    window.setFramerateLimit(60);

    sf::Texture texture_background;
    if(!texture_background.loadFromFile("background.png")) { return 1; }
    texture_background.setRepeated(true);

    sf::Sprite background;
    background.setTexture(texture_background);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.draw(background);

        window.display();
    }
}
