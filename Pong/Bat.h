#pragma once
#include "GameObject.h"
class Bat : public GameObject
{
protected:

public:
	Bat();
	Bat(const std::string& name = "");
	virtual ~Bat() = default;

	Bat(const Bat&)				= delete;
	Bat(Bat&&)					= delete;
	Bat& operator=(const Bat&)	= delete;
	Bat& operator=(Bat&&)		= delete;

	sf::RectangleShape shape;
	sf::FloatRect prevGlobalBounds;
	
	float speed = 500;


	void Init();
	void Update(float dt);
	void Draw(sf::RenderWindow& window);

};