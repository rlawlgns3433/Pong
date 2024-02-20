#pragma once
#include "Scene.h"

class TextGo;
class Bat;
class Ball;

class SceneGame : public Scene
{
protected :
	GameStatus status = GameStatus::Awake;
	TextGo* textScore = nullptr;
	TextGo* textLives = nullptr;
	TextGo* textGameover = nullptr;
	TextGo* textMessage = nullptr;
	Bat* bat = nullptr;
	Ball* ball = nullptr;

	bool isBallActive = false;
	bool isGameover = false;

	float windowX = 0.f;
	float windowY = 0.f;

public :
	SceneGame(SceneIDs id);
	virtual ~SceneGame();

	SceneGame(const SceneGame&)				= delete;
	SceneGame(SceneGame&&)					= delete;
	SceneGame& operator=(const SceneGame&)	= delete;
	SceneGame& operator=(SceneGame&&)		= delete;

	// SceneDev1을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	virtual void Reset();
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateGameover(float dt);
	void UpdatePause(float dt);
	void Draw(sf::RenderWindow& window);

	void SetStatus(GameStatus newStatus);

};

