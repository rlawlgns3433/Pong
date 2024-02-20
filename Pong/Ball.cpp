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
	const sf::FloatRect& prevBallBounds = shape.getGlobalBounds();
	sf::Vector2f prevPos = shape.getPosition();
	sf::Vector2f pos = prevPos;
	pos += direction * speed * dt;
	shape.setPosition(pos);

	const sf::FloatRect& ballBounds = shape.getGlobalBounds();
	float ballLeft = ballBounds.left;
	float ballRight = ballBounds.left + ballBounds.width;
	float ballTop = ballBounds.top;
	float ballBottom = ballBounds.top + ballBounds.height;

	float windowLeft = windowBounds.left;
	float windowRight = windowBounds.left + windowBounds.width;
	float windowTop = windowBounds.top;
	float windowBottom = windowBounds.top + windowBounds.height;

	const sf::FloatRect& batBounds = bat.shape.getGlobalBounds();
	if (prevBallBounds.intersects(bat.prevGlobalBounds) && ballBounds.intersects(batBounds))
	{
		float batLeft = batBounds.left;
		float batRight = batBounds.left + batBounds.width;
		float batTop = batBounds.top;
		float batBottom = batBounds.top + batBounds.height;

		if (ballBottom > batTop)
		{
			if (ballLeft > batRight || ballRight < batLeft)
			{
				direction.x *= 1.f;
			}
			direction.y *= -1.f;
		}
		else if (ballTop < batBottom)
		{
			direction.y *= -1.f;
		}
		else if (ballLeft > batRight || ballRight < batLeft)
		{
			direction.x *= 1.f;
		}

		SCENE_MANAGER.SetScore(SCENE_MANAGER.GetScore() + 1);
		shape.setPosition(prevPos);
		isBoundBat = true;
	}

	if (ballBottom > windowBottom + 300) // ¾Æ·§¸é Ãæµ¹
	{
		isDead = true;
		shape.setPosition(prevPos);
		direction.y *= -1;
	}
	else if (ballTop < windowTop) // À­¸é Ãæµ¹
	{
		shape.setPosition(prevPos);
		direction.y *= -1;
	}
	else if(ballLeft < windowLeft || ballRight > windowRight) // ÁÂ¿ì Ãæµ¹
	{
		shape.setPosition(prevPos);
		direction.x *= -1;
	}
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
