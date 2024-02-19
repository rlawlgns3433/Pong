#include "pch.h"
#include "Ball.h"

Ball::Ball(Bat& bat, const sf::FloatRect& bounds) 
	: bat(bat), windowBounds(bounds)
{
	shape.setRadius(10.f);
	shape.setFillColor(sf::Color::White);

	Utils::SetOrigin(shape, Origins::BC);
}

Ball::Ball(const std::string& name, Bat& bat)
	: GameObject(name), bat(bat)
{
}

void Ball::Update(float dt)
{
	isBoundBat = false;
	isBoundBorder = false;
	sf::Vector2f pos = shape.getPosition();
	pos += direction * speed * dt;
	shape.setPosition(pos);

	const sf::FloatRect& ballBounds = shape.getGlobalBounds();
	const sf::FloatRect& batBounds = bat.shape.getGlobalBounds();

	//Check the intersection between two rectangles.
	if (ballBounds.intersects(batBounds))
	{
		isBoundBat = true;
	}

	if (isBoundBat)
	{
		direction *= -1.f;
	}
	else
	{
		direction = prevDirection;
	}


	if (pos.x < windowBounds.left) 
	{
		pos.x = windowBounds.left;
		direction.x = -direction.x;
		Fire(direction, speed);
	}
	else if (pos.x + shape.getRadius() > windowBounds.left + windowBounds.width) 
	{
		pos.x = windowBounds.left + windowBounds.width - shape.getRadius();
		direction.x = -direction.x; 
		Fire(direction, speed);
	}

	if (pos.y < windowBounds.top) 
	{
		pos.y = windowBounds.top - direction.y * dt;
		direction.y = -direction.y;
		Fire(direction, speed);
	}
	else if (pos.y + shape.getRadius() > windowBounds.top + windowBounds.height) 
	{
		isDead = true;
	}

	shape.setPosition(pos);

	prevDirection = direction;

	// ¹Ù´Ú Ãæµ¹ isDead = true

}
void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Ball::Fire(const sf::Vector2f direction, float speed)
{
	this->direction = direction;
	this->speed = speed;
	this->isDead = false;
	this->prevDirection = this->direction;
}
