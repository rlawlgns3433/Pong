#pragma once
#include "Singleton.h"

class Framework : public Singleton<Framework>
{
protected :
	friend class Singleton<Framework>;

public :
	Framework()								   = default;
	virtual ~Framework()					   = default;
	Framework(const Framework& ref)			   = delete;
	Framework(Framework&& ref)			       = delete;
	Framework& operator=(const Framework& ref) = delete;
	Framework& operator=(Framework&& ref)	   = delete;


	sf::RenderWindow window;
	sf::Vector2i windowSize;

	sf::Clock clock;

	sf::Time realTime; // 게임 시작부터 경과 시간
	sf::Time time; // 게임 시작부터 경과 시간 (timeScale이 적용된 시간)

	sf::Time realDeltaTime;
	sf::Time deltaTime;

	float timeScale = 1.f;

public:
	sf::RenderWindow& GetWindow() { return window; } // 조심할 필요가 있음
	const sf::Vector2i& GetWindowSize() const { return windowSize; }

	float GetRealTime()			const { return realTime.asSeconds(); }
	float GetTime()				const { return time.asSeconds(); }
	float GetRealDeltaTime()	const { return realDeltaTime.asSeconds(); }
	float GetDeltaTime()		const { return deltaTime.asSeconds(); }
	float GetTimeScale()		const { return timeScale; }
	void SetTimeScale(const float scale) { this->timeScale = scale; }

	virtual void Init(int width, int height, const std::string& name = "Game");
	virtual void Do();
	virtual void Release();

};

#define FRAMEWORK (Singleton<Framework>::Instance())