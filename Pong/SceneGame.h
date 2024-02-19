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
	Bat* bat = nullptr;
	Ball* ball = nullptr;

	unsigned lives = 0;
	unsigned score = 0;
	bool isBallActive = false;

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
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window);

	void SetStatus(GameStatus newStatus);

};

