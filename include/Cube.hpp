/* Cube.hpp */
#ifndef CUBE_HPP
#define CUBE_HPP

#include <array>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Cube {
public:
    Cube();
    
    void display_in_terminal() const;
    void move(std::string move);
    
    void draw(sf::RenderWindow &window);
private:
    std::array<std::array<char, 9>, 6> faces;
    void rotateFace(int face);
    void moveU();
    void moveD();
    void moveL();
    void moveR();
    void moveF();
    void moveB();
    void printOne(char c) const;
    void drawCubeFace(sf::RenderWindow &window, sf::Vector3f pos, int j, int i, char fixed_axis);
    sf::Color getCubieFaceColor(char face, int j, int i);
    sf::Vector2f toIsometric(float x, float y, float z);
    void printAxis(sf::RenderWindow &window);
    
};

#endif
