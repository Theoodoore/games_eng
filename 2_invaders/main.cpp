#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

//Main.cpp
sf::Texture spritesheet;
sf::Sprite invader;

void Load() {
    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    invader.setTexture(spritesheet);
    invader.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(32, 32)));
}

void Render(RenderWindow& window) {
    window.draw(invader);
}

int main() {
    RenderWindow window(sf::VideoMode({ 200, 200 }), "Working");
    Load();

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.display();
    }
    return 0;
}