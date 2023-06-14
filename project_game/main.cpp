//---------------------------------------------------
//   mail: mikolaj.michalek@student.put.poznan.pl
//---------------------------------------------------
//   mail: antoni.martinek.1@student.put.poznan.pl
//---------------------------------------------------

#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

int main()
{
    //Window
    int window_x = 900.0;
    int window_y = 600.0;
    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "Spiky bird", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev;

    //Game loop
    while (window.isOpen())
    {
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if(ev.key.code == sf::Keyboard::Escape)
                    window.close();
                break;
            }
        }

        //Update

        //Render
        window.clear(sf::Color::Black);

        //Draw your game

        window.display();
    }
    return 0;
}
