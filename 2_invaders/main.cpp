//main.cpp
#include "Ship.h"
#include "game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

sf::Texture spritesheet;
sf::Sprite invader;
std::vector<Ship*> ships;

Player* player = nullptr;

void Reset() {
    // Reset code to go here
}

void Load() {
    if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
        cerr << "Failed to load spritesheet!" << std::endl;
    }

    Bullet::Init();

    float totalWidth = invaders_columns * invaderSize + (invaders_columns - 1) * (invaderSize - invaderSize);
    
    float startX = (gameWidth - totalWidth) / 2.0f;

    float startY = 100.0f;

    for (int r = 0; r < invaders_rows; ++r) {
        auto rect = IntRect(Vector2i(0, 0), Vector2i(32, 32));
        for (int c = 0; c < invaders_columns; ++c) {
            float xPos = startX + c * (invaderSize + padding);
            float yPos = startY + r * (invaderSize + padding);

            Invader* inv = new Invader(rect, sf::Vector2f(xPos, yPos));
            inv->direction = true;
            inv->speed = 75.f;
            ships.push_back(inv);
        }
    }

    player = new Player();
    ships.push_back(player);
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
        s->Update(dt); // Call update function for each ship in ships vector
    }

    Bullet::Update(dt);
}

void Render(RenderWindow& window) {
    //window.draw(invader);
    for (const auto& s : ships) {
        window.draw(*s);
    }
    Bullet::Render(window);
}

int main() {
    RenderWindow window(sf::VideoMode({ gameWidth, gameHeight }), "Working");
    Load();

    while (window.isOpen()) {
        window.clear();
		Update(window);
		Render(window);
        window.display();
    }
    return 0;
}