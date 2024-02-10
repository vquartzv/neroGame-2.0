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
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);

        // end the current frame
        window.display();
        window.draw(rectangle);
    }

    return 0;
}




void map::getWin(int size, std::vector<poin>* box){
	sf::RectangleShape rectangle;
    sf::VertexArray grid;
    sf::RenderWindow window;
	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	window.create(mode, "My window", sf::Style::Fullscreen);
    window.setFramerateLimit(60);
    int sizeBoxX=size;
    int sizePoin=(window.getSize().x-40)/sizeBoxX;
    int sizeX=window.getSize().x-40;
    rectangle.setSize(sf::Vector2f(sizeX, sizeX));
	rectangle.setPosition(20, 20);
	grid.setPrimitiveType(sf::Lines);
	sf::Color gridColor = sf::Color::Black;
	for (int y = 20; y <= sizeX; y += sizePoin)
    {
        // добавляем две вершины для каждой линии
        grid.append(sf::Vertex(sf::Vector2f(20, y), gridColor)); // левый конец линии
        grid.append(sf::Vertex(sf::Vector2f(window.getSize().x-20, y), gridColor)); // правый конец линии
    }
    for (int x = 20; x <= sizeX; x += sizePoin)
    {
        // добавляем две вершины для каждой линии
        grid.append(sf::Vertex(sf::Vector2f(x, 20), gridColor)); // верхний конец линии
        grid.append(sf::Vertex(sf::Vector2f(x, sizeX+20), gridColor)); // нижний конец линии
    }
    sf::Color color = sf::Color::Green;
	sf::Event event;
	while (window.pollEvent(event)){
	               if (event.type == sf::Event::Closed){
                window.close();
            };
        };
     while(window.isOpen()){
        window.clear(sf::Color::Blue);
        window.draw(rectangle);
        window.draw(grid);
        
        window.draw(squares);
        window.display();
     };
     
};

void map::drawWin(){
	
};