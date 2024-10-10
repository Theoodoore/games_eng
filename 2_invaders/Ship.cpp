#include "Ship.h"
#include "game.h"
#include "bullet.h"
using namespace sf;
using namespace std;

Ship::Ship() {};

Ship::Ship(IntRect ir) : Sprite() {
    _sprite = ir;
    setTexture(spritesheet);
    setTextureRect(_sprite);
    _explosionTime = 0.0f;  // Initialize timer to 0
}

void Ship::Update(const float& dt) {
    // Only process explosion logic if the ship has exploded
    if (_exploded && _explosionTime > 0) {
        _explosionTime -= dt;

        // Calculate the fade-out alpha based on the explosion timer
        int alpha = static_cast<int>((_explosionTime / explosionDuration) * 255);
        setColor(Color(255, 255, 255, alpha));

        // Once the explosion timer reaches 0, remove the ship or make it invisible
        if (_explosionTime <= 0) {
            setPosition(Vector2f(-100, -100));  // Move it off-screen
            setColor(Color(255, 255, 255, 0));  // Fully transparent
        }
    }
}

void Ship::Explode() {
    // Trigger explosion only if the ship has not exploded yet
    if (!_exploded) {
        setTextureRect(IntRect(Vector2i(128, 32), Vector2i(32, 32)));  // Set explosion texture
        _exploded = true;  // Mark as exploded
        _explosionTime = explosionDuration;  // Start the explosion timer
        setColor(Color(255, 255, 255, 255));  // Ensure it starts fully opaque
    }
}

bool Ship::is_exploded() const {
    return _exploded;
}

Ship::~Ship() = default;

Invader::Invader() : Ship() {}

bool Invader::direction;
float Invader::speed;

Invader::Invader(sf::IntRect ir, sf::Vector2f pos) : Ship(ir) {
    setOrigin(Vector2f(16.f, 16.f));;
    setPosition(pos);
}

void Invader::MoveDown() {
    move(Vector2f(0.0f, 24.0f));
}

void Invader::Update(const float& dt) {
    // Call the base class Update to handle explosion logic
    Ship::Update(dt);

    // If the invader has exploded, skip the movement logic
    if (_exploded) return;

    // Continue normal invader movement if it hasn't exploded
    move(Vector2f(dt * (direction ? 1.0f : -1.0f) * speed, 0.0f));

    // Handle invader movement direction and bullet firing
    static float fireTime = 0.0f;
    fireTime -= dt;

    // Check for invader movement direction changes at screen edges
    if ((direction && getPosition().x > gameWidth - 16) ||
        (!direction && getPosition().x < 16)) {
        direction = !direction;
        for (auto& s : ships) {
            s->MoveDown();
        }
    }

    // Randomly fire bullets from invaders
    if (fireTime <= 0 && rand() % 100 == 0 && !player->is_exploded()) {
        Bullet::Fire(getPosition(), true);
        fireTime = 4.0f + (rand() % 60);
    }
}

Player::Player() : Ship(IntRect(Vector2i(160, 32), Vector2i(32, 32))) {
    setPosition({ gameWidth * 0.5f, gameHeight - 32.f });
}

void Player::Update(const float& dt) {
    // Call the base class Update to handle explosion logic
    Ship::Update(dt);

    // If the player has exploded, stop further input handling
    if (player->is_exploded()) {
        return;
    }

    float speed = 200.0f;  // Player speed
    static float fireTime = 0.0f;
    fireTime -= dt;

    // Move player left
    if (Keyboard::isKeyPressed(Keyboard::Left) && getPosition().x > 0.0f) {
        move(Vector2f(-speed * dt, 0.0f));
    }

    // Move player right
    if (Keyboard::isKeyPressed(Keyboard::Right) && getPosition().x < gameWidth - invaderSize) {
        move(Vector2f(speed * dt, 0.0f));
    }

    // Fire bullets
    if (fireTime <= 0 && Keyboard::isKeyPressed(Keyboard::Up)) {
        Bullet::Fire(getPosition(), false);  // Fire a player bullet
        fireTime = 0.5f;
    }
}
