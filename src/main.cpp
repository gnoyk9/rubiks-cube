/* main.cpp */
#include "Cube.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
// #include <thread>

int main() {
    Cube cube;
    std::string move;
    // Create a window (800x600 is the size)
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Rubik's Cube");
    sf::CircleShape shape(100.f);
    
    std::cout << "Initial Cube State:\n";
    cube.display_in_terminal();
    
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        cube.draw(window);
        window.display();

        std::cout << "Enter a move (U, D, L, R, F, B) or Q to quit: ";
        std::cin >> move;
        
        if (move == "Q" || move == "q") {
            window.close();
            break;
        }
        cube.move(move);
    }
 
    return 0;
}