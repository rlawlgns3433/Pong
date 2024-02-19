#pragma once
#include "GameObject.h"
#include "Bat.h"

class Ball : public GameObject
{
protected:
	sf::Vector2f prevDirection = { 0.f, 0.f };
	sf::Vector2f direction = { 0.f, 0.f };
	sf::FloatRect windowBounds;
	Bat& bat;

	sf::CircleShape shape;
	float speed = 0.f;
	bool isDead = false;
	bool isBoundBat = false;
	bool isBoundBorder = false;

public:
	Ball(Bat& b, const sf::FloatRect& bounds);
	Ball(const std::string& name, Bat& b);
	virtual ~Ball() = default;

	Ball(const Ball& ref)			= delete;
	Ball(Ball&&)					= delete;
	Ball& operator=(const Ball&)	= delete;
	Ball& operator=(Ball&&)			= delete;

	void Update(float dt);
	void Draw(sf::RenderWindow& window);

	sf::CircleShape& GetShape() { return shape; }

	void SetSpeed(const float speed) { this->speed = speed; }
	float GetSpeed() const { return this->speed; }
	void SetDead(const bool dead) { this->isDead = dead; }
	bool IsDead() const { return this->isDead; }
	void SetBoundBat(const bool boundBat) { this->isBoundBat = boundBat; }
	bool IsBoundBat() const { return this->isBoundBat; }
	void SetBoundBorder(const bool boundBorder) { this->isBoundBat = boundBorder; }
	bool IsBoundBorder() const { return this->isBoundBorder; }
	void Fire(const sf::Vector2f direction, float speed);
};