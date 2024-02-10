#include <SFML/Graphics.hpp>

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    
    
    // define a 120x50 rectangle
sf::RectangleShape rectangle(sf::Vector2f(120.f, 50.f));

// change the size to 100x100
rectangle.setSize(sf::Vector2f(100.f, 100.f));

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        
    }

    return 0;
}