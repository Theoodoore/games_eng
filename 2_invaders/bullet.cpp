//bullet.cpp
#include "bullet.h"
#include "Ship.h"
#include "game.h"
using namespace sf;
using namespace std;

Bullet Bullet::bullets[256]; // Bullet pool
unsigned char Bullet::bulletPointer = 0; // Points to next available bulet

Bullet::Bullet() : _mode(false) {
	//Initialise bullet position off-screen to indicate it is inactive
	setPosition(-100, -100);
}

void Bullet::Init() {
	for (auto& bullet : bullets) {
		bullet.setTexture(spritesheet);
		bullet.setTextureRect(IntRect(Vector2i(32, 32), Vector2i(32, 32)));
		bullet.setOrigin(16.f, 16.f);
	}
}

void Bullet::Fire(const sf::Vector2f& pos, const bool mode) {
	if (bulletPointer < 256) {
		Bullet& bullet = bullets[bulletPointer++];
		bullet.setPosition(pos); //Set the bullet position to where its fired from
		bullet._mode = mode; //Set the bullet type (enemy/player)
		bulletPointer = (bulletPointer + 1) % 256;
	}
}

void Bullet::_Update(const float& dt) {
	if (getPosition().y < -32 || getPosition().y > gameHeight + 32) {
		//Off screen - do nothing
		return;
	}
	else {
		move(Vector2f(0, dt * 200.0f * (_mode ? 1.0f : -1.0f)));
		const FloatRect boundingBox = getGlobalBounds();

		for (auto s : ships) {
			if (!_mode && s == player) {
				//player bullets don't collide with player
				continue;
			}
			if (_mode && s != player) {
				//invader bullets don't collide with other invaders
				continue;
			}
			if (!s->is_exploded() &&
				s->getGlobalBounds().intersects(boundingBox)) {
					//Explode the ship
				s->Explode();
				//warp bullet off-screen
				setPosition(Vector2f(-100, -100));
				return;
				}
		}
	}
}

void Bullet::Update(const float& dt) {
	for (int i = 0; i < bulletPointer; ++i) {
		bullets[i]._Update(dt);
	}
}

void Bullet::Render(sf::RenderWindow& window) {
	for (int i = 0; i < bulletPointer; ++i) {
		window.draw(bullets[i]); //Draw each bullet in the pool
	}
}