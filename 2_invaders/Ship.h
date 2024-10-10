//ship.h
#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
protected:
	sf::IntRect _sprite;
	bool _exploded = false;
	float _explosionTime = 0.0f;
	const float explosionDuration = 1.0f;
	//Default constructor is hidden
	Ship();
public:
	//Constructor that takes a sprite
	explicit Ship(sf::IntRect ir);
	//Update, virtual so can be overriden, but not pure virtual
	virtual void Update(const float& dt);
	//Virtual function, default does nothing
	virtual void MoveDown() {}
	bool is_exploded() const;
	virtual void Explode();
	//Pure virtual deconstructor -- makes this an abstract class and avoids undefined behaviour
	virtual ~Ship() = 0;
};

class Invader : public Ship {
public:
	static bool direction;
	static float speed;
	Invader(sf::IntRect ir, sf::Vector2f pos);
	Invader();
	void MoveDown() override;
	void Update(const float& dt) override;
};

class Player : public Ship {
public:
	Player();
	void Update(const float& dt) override;
};