//main.cpp
#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

sf::Texture spritesheet;
sf::Sprite invader;
std::vector<Ship*> ships;

void Load() {
    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }
    Invader* inv = new Invader(sf::IntRect(Vector2i(0, 0), Vector2i(32, 32)), { 100,100 } );
    Invader* inv2 = new Invader(sf::IntRect(Vector2i(32, 0), Vector2i(32, 32)), { 132,100 });
    Invader* inv3 = new Invader(sf::IntRect(Vector2i(64, 0), Vector2i(32, 32)), { 68,100 });
    ships.push_back(inv);
    ships.push_back(inv2);
    ships.push_back(inv3);
}

void Update(RenderWindow& window){
	static Clock clock;
	float dt = clock.restart().asSeconds();
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

    // Update all ships
    for (auto& s : ships) {
        s->Update(dt); // Call updatae function for each ship in ships vector
    }
}

void Render(RenderWindow& window) {
    //window.draw(invader);
    for (const auto& s : ships) {
        window.draw(*s);
    }
}

int main() {
    RenderWindow window(sf::VideoMode({ 200, 200 }), "Working");
    Load();

    while (window.isOpen()) {
        window.clear();
		Update(window);
		Render(window);
        window.display();
    }
    return 0;
}