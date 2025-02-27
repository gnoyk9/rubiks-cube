/* Cube.cpp */
#include "Cube.hpp"
#include <span>
#include <cmath>

#define RESET   "\033[0m"
#define RED     "\033[38;2;255;0;0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[38;2;255;255;0m"
#define BLUE    "\033[38;2;0;0;255m"
#define ORANGE  "\033[38;2;255;165;0m"
#define CYAN    "\033[36m"
#define WHITE   "\033[38;2;255;255;255m"

#define SPACE   "      "

Cube::Cube() {
    // Initialize cube with standard color scheme
    char colors[6] = {'O', 'B', 'Y', 'G',  'R',  'W'};
    for (int i = 0; i < 6; ++i) {
        faces[i].fill(colors[i]);
    }
}

void Cube::display_in_terminal() const {
    for (int i = 0; i < 3; ++i) {
        std::cout << SPACE;
        for (char c : std::span(faces[0]).subspan(i*3, 3)) {
            printOne(c);
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < 3; ++i) {
        for (int j= 1; j < 4; j++) {
            for (char c : std::span(faces[j]).subspan(i*3, 3)) {
                printOne(c);
            }
        }
        std::cout << std::endl;
    }
    for (int j= 0; j < 2; j++) {
        for (int i = 0; i < 3; ++i) {
            std::cout << SPACE;
            for (char c : std::span(faces[4+j]).subspan(i*3, 3)) {
                printOne(c);
            }
            std::cout << std::endl;
        }
    }
}

void Cube::move(std::string move) {
    if (move == "U" || move == "u") moveU();
    else if (move == "D" || move == "d") moveD();
    else if (move == "L" || move == "l") moveL();
    else if (move == "R" || move == "r") moveR();
    else if (move == "F" || move == "f") moveF();
    else if (move == "B" || move == "b") moveB();
    else std::cout << "Invalid move!" << std::endl;
}

void Cube::moveU() {
    rotateFace(2);
    std::array<std::array<char, 9>, 6> faces_tmp = faces;
    for (int i = 0; i < 3; ++i) {
        std::swap(faces[0][8-i], faces_tmp[1][2+3*i]);
        std::swap(faces[1][2+3*i], faces_tmp[4][i]);
        std::swap(faces[4][i], faces_tmp[3][6-3*i]);
        std::swap(faces[3][6-3*i], faces_tmp[0][8-i]);
    }
}

void Cube::moveD() {
    rotateFace(5);
    std::array<std::array<char, 9>, 6> faces_tmp = faces;
    for (int i = 0; i < 3; ++i) {
        std::swap(faces[0][i], faces_tmp[3][2+3*i]);
        std::swap(faces[3][2+3*i], faces_tmp[4][8-i]);
        std::swap(faces[4][8-i], faces_tmp[1][6-3*i]);
        std::swap(faces[1][6-3*i], faces_tmp[0][i]);
    }
}

void Cube::moveL() {
    rotateFace(1);
    std::array<std::array<char, 9>, 6> faces_tmp = faces;
    for (int i = 0; i < 3; ++i) {
        std::swap(faces[4][3*i], faces_tmp[2][3*i]);
        std::swap(faces[2][3*i], faces_tmp[0][3*i]);
        std::swap(faces[0][3*i], faces_tmp[5][3*i]);
        std::swap(faces[5][3*i], faces_tmp[4][3*i]);
    }
}

void Cube::moveR() {
    rotateFace(3);
    std::array<std::array<char, 9>, 6> faces_tmp = faces;
    for (int i = 0; i < 3; ++i) {
        std::swap(faces[0][2+3*i], faces_tmp[2][2+3*i]);
        std::swap(faces[2][2+3*i], faces_tmp[4][2+3*i]);
        std::swap(faces[4][2+3*i], faces_tmp[5][2+3*i]);
        std::swap(faces[5][2+3*i], faces_tmp[0][2+3*i]);
    }
}

void Cube::moveF() {
    rotateFace(4);
    std::array<std::array<char, 9>, 6> faces_tmp = faces;
    for (int i = 0; i < 3; ++i) {
        std::swap(faces[3][6+i], faces_tmp[2][6+i]);
        std::swap(faces[2][6+i], faces_tmp[1][6+i]);
        std::swap(faces[1][6+i], faces_tmp[5][2-i]);
        std::swap(faces[5][2-i], faces_tmp[3][6+i]);
    }
}

void Cube::moveB() {
    rotateFace(0);
    std::array<std::array<char, 9>, 6> faces_tmp = faces;
    for (int i = 0; i < 3; ++i) {
        std::swap(faces[3][i], faces_tmp[5][8-i]);
        std::swap(faces[2][i], faces_tmp[3][i]);
        std::swap(faces[1][i], faces_tmp[2][i]);
        std::swap(faces[5][8-i], faces_tmp[1][i]);
    }
}

void Cube::rotateFace(int face) {
    std::array<char, 9> face_tmp = faces[face];

    faces[face][0] = face_tmp[6];
    faces[face][1] = face_tmp[3];
    faces[face][2] = face_tmp[0];
    faces[face][3] = face_tmp[7];
    faces[face][5] = face_tmp[1];
    faces[face][6] = face_tmp[8];
    faces[face][7] = face_tmp[5];
    faces[face][8] = face_tmp[2];
}

void Cube::printOne(char c) const {
    std::string color;
    switch (c) {
        case 'W': color = WHITE; break;
        case 'Y': color = YELLOW; break;
        case 'G': color = GREEN; break;
        case 'B': color = BLUE; break;
        case 'R': color = RED; break;
        case 'O': color = ORANGE; break;
        default: color = RESET; break;
    }
    std::cout << color << "O " << RESET;
}

void Cube::draw(sf::RenderWindow &window) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {   
                // Draw front face
                drawCubeFace(window, sf::Vector3f(j * 30, i * 30, 90), j, i, 'F');

                // Draw top face
                drawCubeFace(window, sf::Vector3f(j * 30, 0, i * 30), j, i, 'T');

                // Draw side face
                drawCubeFace(window, sf::Vector3f(90, j * 30, i * 30), j, i, 'R');
        }
    }
    // printAxis(window);
}

void Cube::drawCubeFace(sf::RenderWindow &window, sf::Vector3f pos, int j, int i, char face) {

    sf::ConvexShape cubieFace(4);

    float sizeFixedX = face == 'R' ? 28 : 0;
    float sizeFixedY = face == 'T' ? 28 : 0;
    float sizeFixedZ = face == 'F' ? 28 : 0;
    
    // Define the 4 corners of the cubieFace in 3D
    sf::Vector2f p1 = toIsometric(pos.x, pos.y, pos.z);
    sf::Vector2f p2 = toIsometric(pos.x + sizeFixedZ + sizeFixedY, pos.y + sizeFixedX, pos.z);
    sf::Vector2f p3 = toIsometric(pos.x + sizeFixedZ + sizeFixedY, pos.y + sizeFixedZ + sizeFixedX, pos.z + sizeFixedY + sizeFixedX);
    sf::Vector2f p4 = toIsometric(pos.x, pos.y + sizeFixedZ, pos.z + sizeFixedY + sizeFixedX);

    // Assign points
    cubieFace.setPoint(0, p1);
    cubieFace.setPoint(1, p2);
    cubieFace.setPoint(2, p3);
    cubieFace.setPoint(3, p4);

    // Set color
    cubieFace.setFillColor(getCubieFaceColor(face, j, i));
    
    // Draw
    window.draw(cubieFace);
}

sf::Color Cube::getCubieFaceColor(char face, int j, int i) {
    int faceIndex = face == 'T' ? 2 : face == 'R' ? 3 : 4;
    sf::Color color;
    switch (faces[faceIndex][3*i+j]) {
        case 'W': color = sf::Color::White; break;
        case 'Y': color = sf::Color::Yellow; break;
        case 'G': color = sf::Color::Green; break;
        case 'B': color = sf::Color::Blue; break;
        case 'R': color = sf::Color::Red; break;
        case 'O': color = sf::Color(255, 165, 0); break;
    }
    return color;
}

sf::Vector2f Cube::toIsometric(float x, float y, float z) {
    float offset = 400.0;
    float isoX = (x - z) * std::cos(30 * M_PI / 180) + offset;
    float isoY = (x + 2 * y + z) * std::sin(30 * M_PI / 180) + offset;
    return { isoX, isoY };
}

void Cube::printAxis(sf::RenderWindow &window) {
    sf::VertexArray x_axis(sf::PrimitiveType::LineStrip, 2);
    x_axis[0].color = sf::Color::Red;
    x_axis[1].color = sf::Color::Red;
    sf::VertexArray y_axis(sf::PrimitiveType::LineStrip, 2);
    y_axis[0].color = sf::Color::Green;
    y_axis[1].color = sf::Color::Green;
    sf::VertexArray z_axis(sf::PrimitiveType::LineStrip, 2);
    z_axis[0].color = sf::Color::Blue;
    z_axis[1].color = sf::Color::Blue;


    sf::Vector2f origin = toIsometric(0, 0, 0);
    sf::Vector2f x = toIsometric(400, 0, 0);
    sf::Vector2f y = toIsometric(0, 400, 0);
    sf::Vector2f z = toIsometric(0, 0, 400);

    x_axis[0].position = origin;
    x_axis[1].position = x;
    window.draw(x_axis);
    y_axis[0].position = origin;
    y_axis[1].position = y;
    window.draw(y_axis);
    z_axis[0].position = origin;
    z_axis[1].position = z;
    window.draw(z_axis);
}
