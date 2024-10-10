//game.h
#pragma once
#include <SFML/Graphics.hpp>

#include "Ship.h"
#include "bullet.h"

// Game window dimensions
constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;

// Invader settings
constexpr uint16_t invaders_rows = 5;
constexpr uint16_t invaders_columns = 12;
constexpr float invaderSize = 32.0f;
constexpr float startY = 100.0f;
constexpr float padding = 10.0f;
extern Player* player;

extern sf::Texture spritesheet;
extern std::vector<Ship*> ships;