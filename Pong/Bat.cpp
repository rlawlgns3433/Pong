#include "pch.h"
#include "Bat.h"

Bat::Bat(const std::string& name)
	: GameObject(name)
{
	shape.setSize({ 100.f, 5.f });
	shape.setPosition({ 960.f, 1055.f });
	shape.setFillColor(sf::Color::White);

	Utils::SetOrigin(shape, Origins::TC);
}

void Bat::Init()
{
}

void Bat::Update(float dt)
{
 	float h = InputManager::GetAxis(Axis::Horizontal);
	sf::Vector2f pos = shape.getPosition();
	pos.x += h * speed * dt;
	shape.setPosition(pos);
}

void Bat::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
