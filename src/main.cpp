/* main.cpp */
#include "Cube.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

int main() {
    Cube cube;
    std::string move;
    // Create a window (800x600 is the size)
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Rubik's Cube");
    sf::CircleShape shape(100.f);

    const auto onClose = [&window](const sf::Event::Closed&)
    {
        window.close();
    };

    const auto onKeyPressed = [&window, &cube](const sf::Event::KeyPressed& keyPressed)
    {
        if (keyPressed.scancode == sf::Keyboard::Scancode::Escape)
            window.close();
        if (keyPressed.scancode == sf::Keyboard::Scancode::U) {
            cube.move("U");
        } else if (keyPressed.scancode == sf::Keyboard::Scancode::D) {
            cube.move("D");
        } else if (keyPressed.scancode == sf::Keyboard::Scancode::L) {
            cube.move("L");
        } else if (keyPressed.scancode == sf::Keyboard::Scancode::R) {
            cube.move("R");
        } else if (keyPressed.scancode == sf::Keyboard::Scancode::F) {
            cube.move("F");
        } else if (keyPressed.scancode == sf::Keyboard::Scancode::B) {
            cube.move("B");
        }
    };
    
    std::cout << "Initial Cube State:\n";
    cube.display_in_terminal();
    
    while (window.isOpen()) {
        window.handleEvents(onClose, onKeyPressed);
        window.clear();
        cube.draw(window);
        window.display();
    }
 
    return 0;
}
